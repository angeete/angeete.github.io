import pygame as pg

#Set false values as empty space, closed space will have value 1
_ = False
mini_map = [
      [5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5],
      [5,_,_,_,_,_,_,_,_,_,_,_,_,_,_,5,_,_,_,5],
      [5,_,_,6,6,6,6,_,_,_,6,6,6,_,_,5,_,_,_,5],
      [5,_,_,_,_,_,6,_,_,_,_,_,6,_,_,5,_,_,_,5],
      [5,_,_,_,_,_,6,_,_,_,_,_,6,_,_,5,_,_,_,5],
      [5,_,_,6,6,6,6,_,_,6,_,_,_,_,_,5,_,_,_,5],
      [5,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,5],
      [5,_,_,6,6,_,_,6,_,_,_,_,_,_,6,6,_,_,_,5],
      [5,_,_,_,_,_,_,_,_,_,_,_,_,_,_,6,_,_,_,5],
      [5,5,_,_,_,_,_,6,_,_,6,6,6,_,_,6,_,_,_,5],
      [5,_,_,_,_,_,_,_,_,_,_,6,_,_,_,6,6,_,_,5],
      [5,_,_,5,5,5,5,5,_,_,_,_,_,_,_,_,_,_,_,5],
      [5,_,_,_,_,_,_,5,_,_,_,6,_,_,_,6,_,_,_,5],
      [5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5],
]

class Map:
    def __init__(self, game):
        self.game = game
        self.mini_map = mini_map
        self.world_map = {}
        self.get_map()

    def get_map(self):
        for j, row in enumerate(self.mini_map):
            for i, value in enumerate(row):
                if value:
                    self.world_map[(i,j)] = value

    def draw(self):
        [pg.draw.rect(self.game.screen, 'darkgray', (pos[0]* 100, pos[1]*100, 100, 100),2)
        for pos in self.world_map]

