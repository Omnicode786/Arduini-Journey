import pygame
import serial
import math
import time

ser = serial.Serial('COM4', 115200, timeout=1)

pygame.init()
screen = pygame.display.set_mode((800, 800))
pygame.display.set_caption("Ultrasonic Radar")
clock = pygame.time.Clock()
center = (400, 400)
radius = 350

ping = pygame.mixer.Sound("radarmusic.wav")

blips = {}

def polar_to_cartesian(angle_deg, distance):
    angle_rad = math.radians(angle_deg)
    x = center[0] + math.cos(angle_rad) * distance * 3  
    y = center[1] - math.sin(angle_rad) * distance * 3
    return int(x), int(y)

while True:
    screen.fill((0, 0, 0))

    # Radar grid
    pygame.draw.circle(screen, (0, 255, 0), center, radius, 1)
    for r in range(50, radius, 50):
        pygame.draw.circle(screen, (0, 100, 0), center, r, 1)
    for a in range(0, 181, 30):
        x = center[0] + math.cos(math.radians(a)) * radius
        y = center[1] - math.sin(math.radians(a)) * radius
        pygame.draw.line(screen, (0, 100, 0), center, (x, y), 1)

    # Read serial
    try:
        line = ser.readline().decode().strip()
        if line and ',' in line:
            parts = line.split(',')
            ang = int(parts[0])
            dist = int(parts[1])
            if 10 < dist < 100:
                blips[ang] = {'dist': dist, 'timestamp': time.time()}
                ping.play()
    except Exception as e:
        print("Error:", e)

    # Draw blips
    now = time.time()
    for ang, data in list(blips.items()):
        if now - data['timestamp'] > 0.3:
            del blips[ang]
            continue
        pos = polar_to_cartesian(ang, data['dist'])
        pygame.draw.circle(screen, (0, 255, 0), pos, 6)
        # Distance label
        font = pygame.font.SysFont(None, 20)
        text = font.render(f"{data['dist']}cm", True, (0, 255, 0))
        screen.blit(text, (pos[0] + 5, pos[1]))

    pygame.display.flip()
    clock.tick(60)

    # Exit
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            ser.close()
            pygame.quit()
            exit()
