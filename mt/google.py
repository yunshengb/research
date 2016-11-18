from googleapiclient.discovery import build
import pandas as pd
import os

# Important: Set up your credential
# `export developerKey=<some_key>`
# before running this script.
developerKey = os.getenv("developerKey", None)
service = build('translate', 'v2', developerKey=developerKey)

# A list of (input_query_file_path, output_result_file_path) pairs.
# The input query file must follow the CSV format,
# and should have a header to specify which field has the query (named "query"),
# and each query string should be surrounded by double quotes.
MT_QUERY_FILES = [('../exp/asr_mt/asr_result_fisher.txt', \
	'../exp/asr_mt/mt_result_fisher_google.txt'), \
('../exp/asr_mt/asr_result_librispeech.txt', \
	'../exp/asr_mt/mt_result_librispeech_google.txt'), \
('../exp/asr_mt/asr_result_tedlium.txt', \
	'../exp/asr_mt/mt_result_tedlium_google.txt'), \
('../exp/asr_mt/text/query.txt', \
	'../exp/asr_mt/mt_result_regular_google.txt')]

def ask_google(query):
	'''Run a sentiment analysis request on text within a passed query string'''
	x = service.translations().list(
	  source='en',
	  target='zh-CN',
	  q=query
	).execute()
	return x['translations'][0]['translatedText']

def main():
	'''GO through the two lists, ask Google, and save the result.'''
	for input_file, output_file in MT_QUERY_FILES:
		data = pd.read_csv(input_file)
		file = open(output_file, 'w')
		file.write('text,translation\n')
		for i, query in enumerate(data['query']):
			result = ask_google(query)
			print(i, input_file)
			file.write('"' + query + '",' + str(result) + '\n')
		file.close()

if __name__ == '__main__':
  main()
