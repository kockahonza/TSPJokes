project('TSPJokes', 'c')

tspJokesInc = include_directories('TSPJokes/include')
tspJokesSrc = [
  'TSPJokes/src/algorithms.c',
  'TSPJokes/src/common.c',
  'TSPJokes/src/graph.c',
  'TSPJokes/src/rggs.c',
  'TSPJokes/src/util.c',
  ]

tspJokesLib = library('TSPJokes',
  tspJokesSrc,
  include_directories : tspJokesInc)
executable('experiments', 'main.c',
  link_with : tspJokesLib,
  include_directories : tspJokesInc)
