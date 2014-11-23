class Filme:

	def __init__(self, dist, votos, nota, nome, ano):
		self.dist = dist
		self.votos = int(votos)
		self.nota = float(nota)
		self.nome = nome
		self.ano = int(ano)

	def mostreFilme(self):
		print("      " + self.dist, end="")
		print("\t" + str(self.votos), end="")
		print("\t"  + str(self.nota), end="")
		print("\t" + self.nome, end="")
		print("\t(" + str(self.ano) + ")")