import re
from Filme import Filme

class ListaFilmes:

	def __init__(self, nome, encoding, lista):

		self.lista = []
		self.nFilmes = 0

		if nome != None:
			self.lerArquivo(nome, encoding)
		elif lista != None:
			self.lista = lista

	def insiraFilme(self, filme):
		self.lista.append(filme)
		self.nFilmes += 1

	def lerArquivo(self, nome, encoding):

		print("Carregando " + nome + "...", end="")
		f = open(nome, encoding=encoding)
		lista = []
		for line in f:
			if re.match( r'^      [\.\d]', line):
				toks = line.split()
				nome = []

				i = 3
				while i < len(toks) - 1:
					nome.append(toks[i])
					i += 1
				nome = " ".join(nome)

				ano = re.search(r'\d+', toks[len(toks) - 1]).group()
				filme = Filme(toks[0], toks[1], toks[2], nome, ano)
				self.insiraFilme(filme)

		print("arquivo carregado.")


	def lerFilme(self):

		nome = input("Digite o nome do filme: ")
		ano = input("Digite o ano: ")
		nota = input("Digite a nota: ")
		votos = input("Digite o numero de votos: ")
		dist = input("Digite a distribuicao: ")

		self.insiraFilme(filme)

	def popFilme(self):
		self.nFilmes -= 1
		return self.lista.pop(0)

	def getFilme(self):
		return self.lista[0]

	def removeFilme(self):

		nome = input("Digite parte do nome a ser procurado: ")
		for filme in self.lista:
			if re.match(nome, filme.nome):
				filme.mostreFilme()
				i = input("É esse o filme procurado? [s/n/x] (x para sair): ")
				if i == 's':
					index = lista.index(filme)
					break
				elif i == 'x':
					return

		self.lista.nFilmes -= 1
		return self.lista.pop(index)

	def mostreLista(self):	
		for filme in self.lista:
			filme.mostreFilme()



		
