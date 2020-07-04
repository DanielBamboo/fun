import sys
import pygame
from pygame.locals import *
import math

def lineHitCircle(circleCenter, circleRadius, lineStart, lineEnd):
    if lineStart.x - lineEnd.x == 0:
        distance = abs(circleCenter.y - lineStart.y)
    else:
        a = (lineEnd.y - lineStart.y)/(lineEnd.x - lineStart.x)
        b = (lineStart.x*lineEnd.y - lineEnd.x*lineStart.y)/(lineStart.x - lineEnd.x)
        distance = abs(a*circleCenter.x - circleCenter.y + b)/(math.sqrt(a**2 + b**2));

    #print(distance)
    if distance < 0.007:
        return True

pygame.mixer.init()
pygame.init()

screen = pygame.display.set_mode((960, 640), 0 | HWSURFACE | DOUBLEBUF, 32)
FPSCLOCK = pygame.time.Clock()
RED = pygame.Color("red")
#centerpoint = pygame.math.Vector2(480, 320)
endpoint = pygame.math.Vector2(1000, 0)
endpoint2 = pygame.math.Vector2(-1000, 0)
angle = 0.0
done = False

circleCenters = []
circleCenters.append(pygame.math.Vector2(162, 164))
circleCenters.append(pygame.math.Vector2(532, 35))
circleCenters.append(pygame.math.Vector2(383, 433))
circleCenters.append(pygame.math.Vector2(867, 549))
circleCenters.append(pygame.math.Vector2(547, 362))
circleCenters.append(pygame.math.Vector2(616, 200))

circleCenters.append(pygame.math.Vector2(602, 33))
circleCenters.append(pygame.math.Vector2(232, 578))
circleCenters.append(pygame.math.Vector2(453, 244))
circleCenters.append(pygame.math.Vector2(252, 114))
circleCenters.append(pygame.math.Vector2(305, 300))

centerpoint = circleCenters[0]
preCenterpoint = None

sound = pygame.mixer.Sound('click.wav')

def pause():
    paused = True
    while paused:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_c:
                    paused = False

while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True

    # % 360 to keep the angle between 0 and 360.
    angle = (angle+0.05) % 360
    # The current endpoint is the startpoint vector + the
    # rotated original endpoint vector.

    current_endpoint = centerpoint + endpoint.rotate(angle)
    current_endpoint2 = centerpoint + endpoint2.rotate(angle)

    screen.fill((0, 0, 0))
    pygame.draw.line(screen, RED, current_endpoint2, current_endpoint, 2)
    for circleCenter in circleCenters:
        if circleCenter == centerpoint:
            pygame.draw.circle(screen, pygame.Color(0, 255, 0), (int(circleCenter.x), int(circleCenter.y)), 10, 10)
        else:
            pygame.draw.circle(screen, pygame.Color(255, 0, 0), (int(circleCenter.x), int(circleCenter.y)), 10, 10)

    for circleCenter in circleCenters:
        if centerpoint != circleCenter and lineHitCircle(circleCenter, 5, current_endpoint, current_endpoint2):
            #pause()
            if circleCenter != preCenterpoint:
                preCenterpoint = centerpoint
                centerpoint = circleCenter
                sound.play()
            
            break
    #print('pre:', preCenterpoint)
    #print('cur:', centerpoint)
    x, y = pygame.mouse.get_pos();
    print('x:', x, ' y:', y)

    pygame.display.flip()
    FPSCLOCK.tick(120)

pygame.quit()
sys.exit()
