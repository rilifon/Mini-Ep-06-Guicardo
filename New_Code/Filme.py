class Filme:

	def __init__(self, dist, votos, nota, nome, ano):
		self.dist = dist
		self.votos = int(votos)
		self.nota = float(nota)
		self.nome = nome
		self.ano = int(ano)