import re
from Filme import Filme

class ListaFilmes:

	def __init__(self, action):

		self.lista = []
		self.nLinhas = 0
		self.nIgnoradas = 0

		if action == 'carregar':
			self.lista = self.lerArquivo()

	def lerArquivo(self):

		nome = input("carregueLista: Digite o nome do arquivo: ")

		f = open(nome)
		lista = []
		for line in f:
			self.nLinhas += 1
			if re.match( r'^      [\.\d]', line):

				toks = line.split()
				nome = []

				i = 3
				while i < len(toks) - 1:
					nome.append(toks[i])
					i += 1

				ano = re.search(r'\d+', toks[len(toks) - 1]).group()

				lista.append(Filme(toks[0], toks[1], toks[2], nome, ano)

			else:
				self.nIgnoradas += 1
		return lista

	def lerFilme(self):

		nome = input("Digite o nome do filme: ")
		ano = input("Digite o ano: ")
		nota = input("Digite a nota: ")
		votos = input("Digite o numero de votos: ")
		dist = input("Digite a distribuicao: ")

		self.lista.append(Filme(dist, votos, nota, nome, ano))

	def removeFilme(self):

		nome = input("Digite parte do nome a ser procurado: ")
		for filme in self.lista:
			if re.match(nome, filme.nome):
				i = input("É esse o filme procurado? [s/n/x] (x para sair): ")
				if i == 's':
					index = lista.index(filme)
					break
				elif i == 'x':
					return 1

		self.lista.pop(index)
		return 0


		
