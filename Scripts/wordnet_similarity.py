from nltk.corpus import wordnet
from __future__ import division


#tuple1=('link','crow','rat')
#tuple2=('ring','bear','owl')

def Wordnet_sim()

	count_members=0
	total_sim=0
	sim_val=0

	for t1 in tuple1:
		count_members=count_members+1
		max_sim=0

		from1=wordnet.synsets(t1)[0]
		
		for t2 in tuple2:
			from2=wordnet.synsets(t2)[0]
			max_sim=max(max_sim,from1.wup_similarity(from2))
			
		total_sim=total_sim+max_sim

	sim_val=total_sim/count_members
	return sim_val

