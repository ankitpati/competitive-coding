#!/usr/bin/env python3
"""
Clash Game Graphics Code
"""

from tkinter import Canvas, Frame, StringVar, Label
from threading import Thread
from time import sleep


class BeadGraph:
    """
    Bead Graph Class
    """

    def __init__(self, board_graph, bead):
        self.board_graph = board_graph
        self.bead = bead
        self.cell = bead.cell
        self.life_num = bead.life
        self.oval_coords = self.get_oval_coords(bead.cell)
        self.life_coords = self.get_life_coords(bead.cell)
        self.oval_item = board_graph.create_oval(self.oval_coords,
                                                 fill=bead.color)
        self.life_item = board_graph.create_text(self.life_coords,
                                                 text=bead.life)

    def get_oval_coords(self, cell):
        """
        Get Oval Coordinates
        """

        c_x = cell[
            0] * self.board_graph.cell_width + self.board_graph.cell_width / 2
        c_y = cell[
            1] * self.board_graph.cell_width + self.board_graph.cell_width / 2
        r = self.board_graph.cell_width / 2 - 5
        return c_x - r, c_y - r, c_x + r, c_y + r

    def get_life_coords(self, cell):
        """
        Get Life Coordinates
        """

        c_x = cell[
            0] * self.board_graph.cell_width + self.board_graph.cell_width / 2
        c_y = cell[
            1] * self.board_graph.cell_width + self.board_graph.cell_width / 2
        return c_x, c_y

    def update(self):
        """
        Update the Display
        """

        self.move()
        self.life_update()

    @staticmethod
    def get_direction(c1, c2):
        """
        Get Direction
        """

        d0, d1 = c2[0] - c1[0], c2[1] - c1[1]
        if abs(d0) > 1:
            d0 = 1 if d0 < 0 else -1
        if abs(d1) > 1:
            d1 = 1 if d1 < 0 else -1
        return d0, d1

    def move(self):
        """
        Make a Move
        """

        d = self.get_direction(self.cell, self.bead.cell)
        self.cell = self.bead.cell

        old_oval_coord = self.oval_coords
        old_life_coord = self.life_coords

        new_oval_coord = self.get_oval_coords(self.cell)
        new_life_coord = self.get_life_coords(self.cell)

        diff = self.board_graph.cell_width / 20
        x_diff, y_diff = d[0] * diff, d[1] * diff

        cur_oval_coord = old_oval_coord
        cur_life_coord = old_life_coord
        for _ in range(20):
            cur_oval_coord = (cur_oval_coord[0] + x_diff,
                              cur_oval_coord[1] + y_diff,
                              cur_oval_coord[2] + x_diff,
                              cur_oval_coord[3] + y_diff)
            cur_life_coord = (cur_life_coord[0] + x_diff,
                              cur_life_coord[1] + y_diff)
            self.board_graph.coords(self.oval_item, cur_oval_coord)
            self.board_graph.coords(self.life_item, cur_life_coord)
            sleep(0.03)
            self.board_graph.update()

        self.board_graph.coords(self.oval_item, new_oval_coord)
        self.board_graph.coords(self.life_item, new_life_coord)
        self.oval_coords = new_oval_coord
        self.life_coords = new_life_coord

    def life_update(self):
        """
        Life Updates
        """

        old_life = self.life_num
        if self.bead.life < old_life:
            self.board_graph.itemconfig(self.oval_item, fill='black')
            sleep(0.1)
            self.board_graph.itemconfig(self.oval_item, fill=self.bead.color)

        self.life_num = self.bead.life
        self.board_graph.itemconfig(self.life_item, text=self.life_num)
        if self.life_num == 0:
            self.board_graph.remove(self)


class PlayBoardGraph(Canvas):
    """
    Play Board Graph
    """

    def __init__(self, master, board, cell_width):
        self.board = board
        self.cell_width = cell_width
        self.bead_graphs = {}
        super().__init__(master,
                         width=board.width * self.cell_width,
                         height=board.height * self.cell_width)
        self.draw_gird()
        self.pack()

        for bead in self.board.get_beads():
            self.bead_graphs[bead.id] = BeadGraph(self, bead)

    def draw_gird(self):
        """
        Draw Grid
        """

        for column in range(self.board.width):
            for row in range(self.board.height):
                x1 = column * self.cell_width
                y1 = row * self.cell_width
                x2 = x1 + self.cell_width
                y2 = y1 + self.cell_width
                self.create_rectangle(x1,
                                      y1,
                                      x2,
                                      y2,
                                      fill='white',
                                      tags='rect')

    def remove(self, bead_graph):
        """
        Remove Bead from Board
        """

        self.board.slide_to(bead_graph.bead, None)
        self.board.remove(bead_graph.bead)
        self.delete(bead_graph.oval_item)
        self.delete(bead_graph.life_item)
        del self.bead_graphs[bead_graph.bead.id]

    def notify(self, *args, **kwargs):
        """
        Notify
        """

        del args, kwargs

        for bead_id in list(self.bead_graphs.keys()):
            bead_graph = self.bead_graphs[bead_id]
            Thread(target=bead_graph.update, args=()).start()


class ScoreBoardGraph(Frame):
    """
    Score Board Graph
    """

    def __init__(self, master, beads, width, height):
        super().__init__(master, width=width, height=height)
        self.pack()

        self.scores = {}
        for bead in beads:
            bead.register_observer(self)
            score_var = StringVar(self, f'{bead.name}: {bead.life}')
            self.scores[bead.id] = score_var
            label = Label(self,
                          textvariable=score_var,
                          fg=bead.color,
                          font=('Helvetica', 16))
            label.pack()

    def notify(self, bead, *args, **kwargs):
        """
        Notify
        """

        del args, kwargs

        self.scores[bead.id].set(f'{bead.name}: {bead.life}')
