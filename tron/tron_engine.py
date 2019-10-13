import pygame
import random


class Player:
    def __init__(self, name, cycle, screen, res, position, color, size, speed):
        self.name = name
        self.position = position
        self.screen = screen
        self.res = res
        self.color = color
        self.size = size
        self.speed = speed
        self.img = pygame.image.load(cycle)
        self.cycle = self.img

    def init(self, dir):
        self.path = []
        self.direction_list = [dir]
        self.direction = dir
        self.change_direction(dir)

    def drawplayer(self):
        for position in self.path:
            pygame.draw.rect(self.screen, self.color, (position[0], position[1], self.size, self.size))
        self.screen.blit(self.cycle, self.position)

    def collision(self):
        return self.position[0] >= self.res[0] or self.position[0] < 0 or self.position[1] >= self.res[1] or self.position[1] < 0

    def change_direction(self, direction):
        if self.allowed_direction(self.direction_list, direction):
            if direction == "left":
                self.speed[1] = 0
                self.speed[0] = -self.size
                self.cycle = pygame.transform.rotate(self.img, 90)
            elif direction == "right":
                self.speed[1] = 0
                self.speed[0] = self.size
                self.cycle = pygame.transform.rotate(self.img, 270)
            elif direction == "up":
                self.speed[0] = 0
                self.speed[1] = -self.size
                self.cycle = self.img
            elif direction == "down":
                self.speed[0] = 0
                self.speed[1] = self.size
                self.cycle = pygame.transform.rotate(self.img, 180)
            self.direction = direction
            self.direction_list.append(direction)

    def move(self):
        self.position[0] += self.speed[0]
        self.position[1] += self.speed[1]
        self.path.append(self.position[:])

    def collision_with_path(self, paths):
        for path in paths:
            if self.position in path[:-1] and self.speed != [0, 0]:
                return True

    def allowed_direction(self, direction_list, direction):
        if direction == "left":
            return "right" != direction_list[-1]
        if direction == "right":
            return "left" != direction_list[-1]
        if direction == "up":
            return "down" != direction_list[-1]
        if direction == "down":
            return "up" != direction_list[-1]

    def watch_ahead(self, speed, paths):
        for i in range(1, 4):  # see 3 iterations ahead
            if self.position[0] + i*speed[0] in [0, self.res[0]]:
                return random.choice(["up", "down"])
            elif self.position[1] + i*speed[1] in [0, self.res[1]]:
                return random.choice(["right", "left"])
            for path in paths:
                if [self.position[0] + i*speed[0], self.position[1] + i*speed[1]] in path[:-1]:
                    return random.choice(["right", "left", "up", "down"])

    def random_move(self, paths):
        dir = self.watch_ahead(self.speed, paths)
        if dir is None:
            if random.randint(0, 49) == 0:
                self.change_direction(random.choice(["left", "right", "up", "down"]))
        else:
            self.change_direction(dir)
        self.move()
