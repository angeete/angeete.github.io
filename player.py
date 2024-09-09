import pygame as pg
import math
from settings import*

class Player:
    def __init__(self, game):
        self.game = game
        self.x, self.y = PLAYER_POS
        self.angle = PLAYER_ANGLE

    def movement(self):
        sin_a = math.sin(self.angle)
        cos_a = math.cos(self.angle)
        dx, dy = 0,0
        speed = PLAYER_SPEED*self.game.delta_time
        speed_sin = sin_a * speed
        speed_cos = cos_a * speed

        #Change player position
        keys = pg.key.get_pressed()
        if keys[pg.K_w]:
            dx += speed_cos
            dy += speed_sin
        if keys[pg.K_s]:
            dx += -speed_cos
            dy += -speed_sin
        if keys[pg.K_a]:
            dx += speed_sin
            dy += -speed_cos
        if keys[pg.K_d]:
            dx += -speed_sin
            dy += speed_cos

        self.check_wall_collision(dx,dy)

        #Change player angle(keys)
        self.rel = 0
        if keys[pg.K_LEFT]:
            #self.angle -= PLAYER_ROT_SPEED * self.game.delta_time
            self.angle -=  PLAYER_ROT_SPEED * self.game.delta_time
            self.rel -= 50
        if keys[pg.K_RIGHT]:
            #self.angle += PLAYER_ROT_SPEED * self.game.delta_time
            self.angle += PLAYER_ROT_SPEED * self.game.delta_time
            self.rel += 50
        self.angle %= math.tau

    def check_wall(self,x,y):
        return(x,y) not in self.game.map.world_map

    def check_wall_collision(self, dx, dy):
        scale = PLAYER_SIZE_SCALE / self.game.delta_time
        if self.check_wall(int(self.x+dx * scale), int(self.y)):
            self.x += dx
        if self.check_wall(int(self.x), int(self.y+dy * scale)):
            self.y += dy


    def draw(self):
        #pg.draw.line(self.game.screen, 'yellow', (self.x*100, self.y*100),
                     #(self.x*100 + WIDTH *math.cos(self.angle),
                     #self.y*100 + HEIGHT *math.sin(self.angle)), 2)
        pg.draw.circle(self.game.screen, 'green', (self.x*100, self.y*100), 15)

    def mouse_control(self):
        mx, my = pg.mouse.get_pos()
        if mx < MOUSE_BORDER_LEFT or mx > MOUSE_BORDER_RIGHT:
           pg.mouse.set_pos([HALF_WIDTH, HALF_HEIGHT])
        self.rel = pg.mouse.get_rel()[0]
        self.rel = max(-MOUSE_MAX_REL, min(MOUSE_MAX_REL, self.rel))
        self.angle += self.rel * MOUSE_SENSITIVITY * self.game.delta_time

    def update(self):
        #ORDER MATTERS, THE ONE THAT IS CALLED SECOND WILL DETERMINE HOW SKY OFFSET WORKS
        self.movement()  # KEYS
        self.mouse_control() #MOUSE


    @property
    def pos(self):
        return self.x, self.y

    @property
    def map_pos(self):
        return int(self.x), int(self.y)

    #W key logic
    #dx = speed*cos(a)
    #dy = speed*sin(a)
    #Where a is the player angle
    #S key logic
    # dx = -speed*cos(a)
    # dy = -speed*sin(a)
    #A key logic
    # dx = speed*sin(a)
    # dy = -speed*cos(a)
    #D key logic
    # dx = -speed*sin(a)
    # dy = speed*cos(a)






