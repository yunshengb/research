from nltk.translate.bleu_score import sentence_bleu
from nltk.tokenize.stanford_segmenter import StanfordSegmenter
import os

curr_dir = os.path.abspath(os.path.dirname(__file__))
os.environ['CLASSPATH'] = curr_dir # add slf4j-api.jar to classpath

class Evaluator(object):
	def __init__(self):
		self.segmenter = StanfordSegmenter( \
			path_to_jar=curr_dir + '/segmenter/stanford-segmenter-3.6.0.jar', \
			path_to_sihan_corpora_dict=curr_dir + '/segmenter/data', \
			path_to_model=curr_dir + '/segmenter/data/pku.gz', \
			path_to_dict=curr_dir + '/segmenter/data/dict-chris6.ser.gz')
		self.segments_seen = {}

	def evaluate(self, result, correct):
		result = self.segmenter.segment(result).split()
		print(result)
		if correct in self.segments_seen:
			correct = self.segments_seen[segments_seen]
		else:
			self.segments_seen[correct] = \
			self.segmenter.segment(correct).split()
			correct = self.segments_seen[correct]
		print(correct)
		score = sentence_bleu([correct], result)
		print('Score:', score)
		return score

if __name__ == '__main__':
	e = Evaluator()
	score = e.evaluate(u'人生十分短促，我们不应该浪费时间。', \
		u'人生十分短暂，我们不应该浪费时间。')
	print('Score:', score)
