import argparse
from googleapiclient import discovery
import httplib2
import json
from oauth2client.client import GoogleCredentials
import math
import pandas as pd

# Important: Set up your credential
# `export GOOGLE_APPLICATION_CREDENTIALS=<somewhere>.json`
# before running this script.
# See tutorial:
# https://cloud.google.com/natural-language/docs/sentiment-tutorial.

# A list of (input_query_file_path, output_result_file_path) pairs.
# The input query file must follow the CSV format,
# and should have a header to specify which field has the query (named "query"),
# and each query string should be surrounded by double quotes.
SA_QUERY_FILES = [('../exp/asr_sa/asr_result_fisher.txt', \
	'../exp/asr_sa/sa_result_fisher_google.txt'), \
('../exp/asr_sa/asr_result_librispeech.txt', \
	'../exp/asr_sa/sa_result_librispeech_google.txt'), \
('../exp/asr_sa/asr_result_tedlium.txt', \
	'../exp/asr_sa/sa_result_tedlium_google.txt'), \
('../exp/asr_sa/text/query.txt', \
	'../exp/asr_sa/sa_result_regular_google.txt')]

DISCOVERY_URL = ('https://{api}.googleapis.com/'
				 '$discovery/rest?version={apiVersion}')

def ask_google(query):
	'''Run a sentiment analysis request on text within a passed query string'''
	http = httplib2.Http()
	credentials = GoogleCredentials.get_application_default().create_scoped(
	  ['https://www.googleapis.com/auth/cloud-platform'])
	http=httplib2.Http()
	credentials.authorize(http)
	service = discovery.build('language', 'v1beta1',
							http=http, discoveryServiceUrl=DISCOVERY_URL)
	service_request = service.documents().analyzeSentiment(
		body={
		'document': {
		'type': 'PLAIN_TEXT',
		'content': query,
		}
	})
	response = service_request.execute()
	polarity = response['documentSentiment']['polarity']
	magnitude = response['documentSentiment']['magnitude']
	return polarity, magnitude

def main():
	'''Go through the two lists, ask Google, and save the result.'''
	for input_file, output_file in SA_QUERY_FILES:
		data = pd.read_csv(input_file)
		file = open(output_file, 'w')
		file.write('query,polarity,magnitude\n')
		for i, query in enumerate(data['query']):
			# Empty string becomes nan in pandas DataFrame, 
			# so check and ignore it.
			if type(query) == float and math.isnan(query):
				continue
			polarity, magnitude = ask_google(query)
			print(i, input_file)
			file.write('"' + query + '",' + str(polarity) + ',' + \
				str(magnitude) + '\n')
		file.close()

if __name__ == '__main__':
  main()
