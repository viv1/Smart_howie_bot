from collections import defaultdict
import random

class CFG(object):
    def __init__(self):
        self.prod = defaultdict(list)

    def add_prod(self, lhs, rhs):
        """ Add production to the grammar. 'rhs' can
            be several productions separated by '|'.
            Each production is a sequence of symbols
            separated by whitespace.

            Usage:
                grammar.add_prod('NT', 'VP PP')
                grammar.add_prod('Digit', '1|2|3|4')
        """
        prods = rhs.split('|')
        for prod in prods:
            self.prod[lhs].append(tuple(prod.split()))

    def gen_random(self, symbol):
        """ Generate a random sentence from the
            grammar, starting with the given
            symbol.
        """
        sentence = ''

        # select one production of this symbol randomly
        rand_prod = random.choice(self.prod[symbol])

        for sym in rand_prod:
            # for non-terminals, recurse
            if sym in self.prod:
                sentence += self.gen_random(sym)
            else:
                sentence += sym + ' '

        return sentence


def main():
    cfg1 = CFG()
    cfg1.add_prod('S', 'NP VP')
    cfg1.add_prod('NP', 'Det N | Det N')
    cfg1.add_prod('NP', 'I | he | she | Joe')
    cfg1.add_prod('VP', 'V NP | VP')
    cfg1.add_prod('Det', 'a | the | my | his')
    cfg1.add_prod('N', 'Martha |  ')
    cfg1.add_prod('V', 'makes | comfortable ')

    for i in xrange(10):
        print cfg1.gen_random('S')


main()
