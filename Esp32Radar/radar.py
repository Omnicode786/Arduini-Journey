import pygame
import serial
import math
import time

# Setup serial (update COM port as needed)
ser = serial.Serial('COM3', 115200, timeout=1)  # Adjust COM port

# Setup Pygame
pygame.init()
screen = pygame.display.set_mode((800, 800))
pygame.display.set_caption("Radar UI")
clock = pygame.time.Clock()
center = (400, 400)
radius = 350

# Load ping sound
ping_sound = pygame.mixer.Sound("radarmusic.wav")

angle = 0
blips = {}  # Dictionary: angle -> distance

def polar_to_cartesian(angle_deg, distance):
    angle_rad = math.radians(angle_deg)
    x = center[0] + math.cos(angle_rad) * distance * 1.5
    y = center[1] - math.sin(angle_rad) * distance * 1.5
    return int(x), int(y)

while True:
    screen.fill((0, 0, 0))

    # Draw radar grid
    pygame.draw.circle(screen, (0, 255, 0), center, radius, 1)
    for r in range(50, radius, 50):
        pygame.draw.circle(screen, (0, 100, 0), center, r, 1)

    for a in range(0, 181, 30):
        x = center[0] + math.cos(math.radians(a)) * radius
        y = center[1] - math.sin(math.radians(a)) * radius
        pygame.draw.line(screen, (0, 100, 0), center, (x, y), 1)

    # Sweep beam
    sweep_angle = angle % 181
    x = center[0] + math.cos(math.radians(sweep_angle)) * radius
    y = center[1] - math.sin(math.radians(sweep_angle)) * radius
    pygame.draw.line(screen, (0, 255, 0), center, (x, y), 2)

    # Read from serial
    try:
        line = ser.readline().decode().strip()
        if line:
            parts = line.split(',')
            if len(parts) == 2:
                ang = int(parts[0])
                dist = int(parts[1])
                blips[ang] = {'dist': dist, 'timestamp': time.time()}
                ping_sound.play()
    except Exception as e:
        print("Error:", e)

    # Draw blips (with short lifespan)
    now = time.time()
    for ang, data in list(blips.items()):
        if now - data['timestamp'] > 0.5:  # 0.5s lifespan
            del blips[ang]
            continue
        pos = polar_to_cartesian(ang, data['dist'])
        pygame.draw.circle(screen, (0, 255, 0), pos, 5)

    pygame.display.flip()
    clock.tick(60)
    angle += 1

    # Exit condition
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            ser.close()
            pygame.quit()
            exit()
