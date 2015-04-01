import nltk.data
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords

english_stops = set(stopwords.words('english'))
words = ["Can't", 'is', 'a', 'contraction']
[word for word in words if word not in english_stops]


word_tokenize("Hi there")