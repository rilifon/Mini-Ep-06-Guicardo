import abc
import Filme
import ListaFilmes
from abc_base import Sorter

class StandardSort(Sorter):

	def nameSort(self, lista):
		lista = sorted(lista, key=lambda filme: filme.nome)
		return

	def noteSort(self, lista):
		lista = sorted(lista, key=lambda filme: filme.nota)
		return