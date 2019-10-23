#!/usr/bin/env python3
"""
Clash Game Driver Code
"""

from random import choice, randint
from tkinter import Tk
from graphics import PlayBoardGraph, ScoreBoardGraph


class Bead:
    """
    Bead Class
    """

    COLORS = ["red", "orange", "green", "brown", "violet"]
    id = 0

    def __init__(self, name):
        """
        :param name: the name of this bead
        """

        self.id = Bead.gen_id()
        self.name = name
        self.cell = ()
        self.life = 3
        self.color = choice(Bead.COLORS)

        Bead.COLORS.remove(self.color)  # DON'T TOUCH THIS LINE
        self.__observers = []  # DON'T TOUCH THIS LINE

    @staticmethod
    def gen_id():
        """
        :return: increment Bead.id by one and return it.
        """

        Bead.id += 1
        return Bead.id

    def get_cell(self):
        """
        :return: self.cell
        """

        return self.cell

    def set_cell(self, new_cell):
        """
        sets self.cell to the given new_cell.
        :param new_cell: a tuple of two integers, representing a cell
        :return: None
        """

        self.cell = new_cell

    def get_life(self):
        """
        :return: self.life
        """

        return self.life

    def collide(self):
        """
        decrement self.life by one
        :return: None
        """

        self.life -= 1

        self.notify_observers()  # DON'T TOUCH THIS LINE

    # You can ignore the rest of methods:
    ######################################################
    def register_observer(self, observer):
        """
        adds the given observer to the list of observers.
        :param observer: an observer to be notified upon bead state change
        """
        self.__observers.append(observer)

    def notify_observers(self, *args, **kwargs):
        """
        this method is called when there is a change in this bead's state.
        as a result all the registered observers will be notified.
        """
        for observer in self.__observers:
            observer.notify(self, *args, **kwargs)


class Board:
    """
    Board Class
    """

    # the valid directions that the beads on this board may slide toward
    DIRS = [(1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (-1, -1), (1, -1),
            (-1, 1)]

    def __init__(self, width, height, beads):
        """
        :param width: number of columns of the board
        :param height: number of rows of the board
        :param beads: list of bead objects on the board
        """

        self.width = width
        self.height = height
        self.beads_dict = {}
        self.cells_with_beads = {}

        for bead in beads:
            self.beads_dict[bead.id] = bead
            self.slide_to(bead, self.get_random_unoccupied_cell())

        self.__observers = []  # ignore this attribute

    def get_beads(self):
        """
        :return: an iterable over the beads on this board.
        """

        return list(self.beads_dict.values())

    def remove(self, bead):
        """
        delete the given bead object

        :param bead: a Bead object.

        :return: None
        """

        del self.beads_dict[bead.id]

        bead_set = self.cells_with_beads.get(bead.cell)
        if bead_set:
            bead_set.discard(bead.id)

        bead.cell = ()

    def get_random_unoccupied_cell(self):
        """
        :return: a random cell on this board which is not occupied by any bead
        """
        def get_random_cell():
            """
            generate a random cell on this board

            :return: tuple of two integers, (a, b),
                     ensure 0 <= a < self.width and 0 <= b < self.height
            """

            return (randint(0, self.width - 1), randint(0, self.height - 1))

        random_cell = get_random_cell()
        while random_cell in self.cells_with_beads:  # cell is occupied
            random_cell = get_random_cell()

        return random_cell

    def next_cell(self, cell, direction):
        """
        :param cell: tuple of two integers representing a cell

        :param direction: an element of Board.DIRS

        :return: destination cell upon starting from cell & following direction

        :raise ValueError: out of the boards bounds upong following direction

        :example: assume you have a 3*3 board, and c = (1, 2), then:
                  next_cell(c, (-1,-1) ) = (0, 1)
                  next_cell(c, (1,0)   ) = (2, 2)
                  next_cell(c, (-1,1)  ) --> raises ValueError
        """

        nxt_cell = (cell[0] + direction[0], cell[1] + direction[1])

        if 0 <= nxt_cell[0] < self.width and 0 <= nxt_cell[1] < self.height:
            return nxt_cell

        raise ValueError


    def valid_directions(self, cell):
        """
        :param cell: cell on this board

        :return: sublist of Board.DIRS which result in a valid destination
        """

        valid_dirs = []
        for direction in Board.DIRS:
            try:
                self.next_cell(cell, direction)
                valid_dirs.append(direction)
            except ValueError:
                pass

        return valid_dirs

    def slide_to(self, bead, destination_cell):
        """
        lifts the given bead from its cell and puts it into another

        :param bead: a bead object on this board

        :param destination_cell: a cell on this board

        :return: None
        """

        def lift():
            """
            assume old_cell = bead.cell

            :return: None
            """

            if not bead.cell:
                return

            bead_set = self.cells_with_beads[bead.cell]
            bead_set.discard(bead.id)
            if not bead_set:
                del self.cells_with_beads[bead.cell]

        def put():
            """
            :return: None
            """

            if not destination_cell:
                return

            bead.cell = destination_cell

            bead_set = self.cells_with_beads.get(bead.cell)
            if bead_set:
                bead_set.add(bead.id)
            else:
                self.cells_with_beads[bead.cell] = set([bead.id])

        lift()
        put()

    def move_beads(self):
        """
        :return: None
        """

        for bead in self.beads_dict.values():
            valid_dirs = self.valid_directions(bead.cell)

            if not valid_dirs:
                continue

            self.slide_to(bead, self.next_cell(bead.cell, choice(valid_dirs)))

    def has_collision(self, cell):
        """
        :param cell: a cell on this board

        :return: True upon collision, False otherwise
        """

        bead_set = self.cells_with_beads.get(cell)
        return len(bead_set) > 1 if bead_set else False

    def perform_collision(self, bead_ids):
        """
        for each bead whose id is in bead_ids, call its collide method.

        :param bead_ids: list of ids of beads on this board that had collision

        :return: None
        """

        for bead in [self.beads_dict[bid] for bid in bead_ids]:
            bead.collide()

    def manage_collisions(self):
        """
        for each cell in self.cells_with_beads, if there are collisions on that
        cell, call self.perform_collision by giving the bead ids that where on
        that cell.

        :return: None
        """

        for bead_set in self.cells_with_beads.values():
            self.perform_collision(list(bead_set))

    def play_one_round(self):
        """
        Play one turn by doing the following:
        1) move beads in random directions
        2) check for collisions and handle them
        3) notify observers about the board's state change.

        :return: None
        """

        self.move_beads()
        self.manage_collisions()

        self.notify_observers()

    # You can ignore the rest of methods:
    ######################################################
    def register_observer(self, observer):
        """
        adds the given observer to the list of observers.
        :param observer: observer to be notified upon state change of board.
        """
        self.__observers.append(observer)

    def notify_observers(self, *args, **kwargs):
        """
        this method is called when there is a change in this board's state.
        as a result all the registered observers will be notified.
        """
        for observer in self.__observers:
            observer.notify(*args, **kwargs)


# You can ignore the the following class:
######################################################
class ClashGame:
    """
    Clash Game Runner
    """

    DELAY = 1000  # time in milliseconds between two turns of this game.

    def __init__(self, master, board):
        self.master = master
        self.board = board

        board_graph = PlayBoardGraph(master, board, 50)
        ScoreBoardGraph(master, self.board.get_beads(), 25, 250)

        self.board.register_observer(board_graph)

        self.master.wm_title("ClashGame")
        self.master.resizable(False, False)

        self.draw(ClashGame.DELAY)

    def draw(self, delay):
        """
        Draw board on screen.
        """

        if not self.gameover():
            self.board.play_one_round()
            self.master.after(delay, lambda: self.draw(delay))

    def gameover(self):
        """
        Check if game is over.
        """

        return len(self.board.get_beads()) <= 1

    def run(self):
        """
        Invoke the main loop of the game.
        """

        self.master.mainloop()


if __name__ == '__main__':
    BEADS = [
        Bead('Stark'),
        Bead('Lannister'),
        Bead('Targaryen'),
        Bead('Martell'),
        Bead('Tyrell')
    ]
    ClashGame(Tk(), Board(5, 5, BEADS)).run()
