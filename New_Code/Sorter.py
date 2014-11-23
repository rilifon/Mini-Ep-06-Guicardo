import Filme
import ListaFilmes
import abc

# Definição retirada de http://ideone.com/Owgfjj, recebe lista de nomes
# de atributos para descobrir se uma classe é subclasse da ABC em questão

def subclasshook(required):
    """Generates a subclass hook based on a simple check for attributes."""

    def __subclasshook__(cls, Check):
        rtn = True
        for r in required:
            if not any(r in vars(BaseClass) for BaseClass in Check.__mro__):
                rtn = NotImplemented
        return rtn

    return __subclasshook__

class Sorter(object):

	__metaclass__ = abc.ABCMeta

	@abc.abstractmethod
	def name(self, lista):
		"""Ordena a lista de filmes por nome"""
		return

	@abc.abstractmethod
	def note(self, lista):
		"""Ordena a lista de filmes por nota"""
		return

	__subclasshook__ = classmethod(subclasshook(["name", "note"]))
