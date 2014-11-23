import sys
import Filme
from ListaFilmes import ListaFilmes
from Sorter import Sorter

class StandardSort(Sorter):
	"""Implementa o sort padrão do Python na lista"""

	def name(self, lista):
		sLista = sorted(lista.lista, key=lambda filme: filme.nome)
		return sLista

	def note(self, lista):
		sLista = sorted(lista.lista, key=lambda filme: filme.nota)
		return sLista

class MergeSort(Sorter):
	"""Implementa o mergesort do código original"""

	def intercala(self, lista, e, d, criterio):
		while e.nFilmes > 0 or d.nFilmes > 0:
			if e.nFilmes > 0 and d.nFilmes > 0:
				if criterio == 'nome' and e.getFilme().nome <= d.getFilme().nome:
					filme = e.popFilme()
					lista.insiraFilme(filme)
				elif criterio == 'nota' and e.getFilme().nota <= d.getFilme().nota:
					filme = e.popFilme()
					lista.insiraFilme(filme)
				elif criterio == 'nome' and e.getFilme().nome > d.getFilme().nome:
					filme = d.popFilme()
					lista.insiraFilme(filme)
				elif criterio == 'nota' and e.getFilme().nota > d.getFilme().nota:
					filme = d.popFilme()
					lista.insiraFilme(filme)
			elif e.nFilmes > 0:
				filme = e.popFilme()
				lista.insiraFilme(filme)
			else:
				filme = d.popFilme()
				lista.insiraFilme(filme)

	def name(self, lista):

		e = ListaFilmes(None, None, None)
		d = ListaFilmes(None, None, None)

		tamanho = lista.nFilmes

		if tamanho <= 1: return lista

		for i in range(int(tamanho/2 + tamanho%2)):
			filme = lista.popFilme()
			e.insiraFilme(filme)

		for i in range(int(tamanho/2)):
			filme = lista.popFilme()
			d.insiraFilme(filme)

		e = self.name(e)
		d = self.name(d)

		self.intercala(lista, e, d, 'nome')

		return lista

	def note(self, lista):

		e = ListaFilmes(None, None, None)
		d = ListaFilmes(None, None, None)

		tamanho = lista.nFilmes

		if tamanho <= 1: return lista

		for i in range(int(tamanho/2 + tamanho%2)):
			e.insiraFilme(lista.popFilme())
		for i in range(int(tamanho/2)):
			d.insiraFilme(lista.popFilme())

		e = self.note(e)
		d = self.note(d)

		self.intercala(lista, e, d, 'nota')

		return lista

if __name__ == "__main__":

	# Testes simples

	lista = ListaFilmes('imdb-ratings-limpo.list', None, None)

	stanSort = StandardSort()
	mergSort = MergeSort()

	# Testando e salvando stanSort.nome()
	print("Ordenando (standard) por nome...", end="")
	standardNameLista = ListaFilmes(None, None, stanSort.name(lista))
	print("completo.")
	sys.stdout = open('standardName.list', 'w')
	standardNameLista.mostreLista()
	sys.stdout = sys.__stdout__
	print("standardName.list criado.")

	# Testando e salvando stanSort.nota()
	print("Ordenando (standard) por nota...", end="")
	standardNoteLista = ListaFilmes(None, None, stanSort.note(lista))
	print("completo.")
	sys.stdout = open('standardNote.list', 'w')
	standardNoteLista.mostreLista()
	sys.stdout = sys.__stdout__
	print("standardNote.list criado.")

	# Testando e salvando mergSort.nome()
	print("Ordenando (merge) por nome...", end="")
	mergeNameLista = mergSort.name(lista)
	print("completo.")
	sys.stdout = open('mergeName.list', 'w')
	mergeNameLista.mostreLista()
	sys.stdout = sys.__stdout__
	print("mergeName.list criado.")

	# Testando e salvando mergSort.nota()
	print("Ordenando (merge) por nota...", end="")
	mergeNoteLista = mergSort.note(lista)
	print("completo.")
	sys.stdout = open('mergeNote.list', 'w')
	mergeNoteLista.mostreLista()
	sys.stdout = sys.__stdout__
	print("mergeNote.list criado.")










