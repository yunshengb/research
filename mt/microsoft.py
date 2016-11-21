import pandas as pd
from os import system

# A list of (input_query_file_path, output_result_file_path) pairs.
# The input query file must follow the CSV format,
# and should have a header to specify which field has the query (named "query"),
# and each query string should be surrounded by double quotes.
MT_QUERY_FILES = [('../exp/asr_mt/asr_result_fisher.txt', \
	'../exp/asr_mt/mt_result_fisher_microsoft.txt'), \
('../exp/asr_mt/asr_result_librispeech.txt', \
	'../exp/asr_mt/mt_result_librispeech_microsoft.txt'), \
('../exp/asr_mt/asr_result_tedlium.txt', \
	'../exp/asr_mt/mt_result_tedlium_microsoft.txt'), \
('../exp/asr_mt/text/query.txt', \
	'../exp/asr_mt/mt_result_regular_microsoft.txt')]

# The token is retrieved through the interactive page
# http://docs.microsofttranslator.com/oauth-token.html
# http://docs.microsofttranslator.com/text-translate.html says, 
# "The acces token is valid for 10 minutes. 
# Obtain a new acces token every 10 minutes, 
# and keep using the same access token for repeated requests
# within these 10 minutes."
# Notice the typo `acces`.
TOKEN = 'eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzY29wZSI6Imh0dHBzOi8vYXBpLm1pY3Jvc29mdHRyYW5zbGF0b3IuY29tLyIsInN1YnNjcmlwdGlvbi1pZCI6ImM3YTA0Nzg5MDZkODRjZjZhYTUyNjAyYTZlNGUzYjkzIiwicHJvZHVjdC1pZCI6IlRleHRUcmFuc2xhdG9yLkYwIiwiY29nbml0aXZlLXNlcnZpY2VzLWVuZHBvaW50IjoiaHR0cHM6Ly9hcGkuY29nbml0aXZlLm1pY3Jvc29mdC5jb20vaW50ZXJuYWwvdjEuMC8iLCJhenVyZS1yZXNvdXJjZS1pZCI6Ii9zdWJzY3JpcHRpb25zL2Q3MGM1MDVkLTQyMGYtNGRjNC1iZTlhLTkzNTIzNjZiOWM3NS9yZXNvdXJjZUdyb3Vwcy9MdWNpZGEvcHJvdmlkZXJzL01pY3Jvc29mdC5Db2duaXRpdmVTZXJ2aWNlcy9hY2NvdW50cy95dW5zaGVuZ2IiLCJpc3MiOiJ1cm46bXMuY29nbml0aXZlc2VydmljZXMiLCJhdWQiOiJ1cm46bXMubWljcm9zb2Z0dHJhbnNsYXRvciIsImV4cCI6MTQ3OTY5MzYyOH0.FiUaSFxHXuuGDGbCJK5Q0gw-wiY57mCnbSHttEhl6xA'

def ask_microsoft(query):
	'''Run a machine translation request on text within a passed query string'''
	cmd = 'curl -X GET --header "Accept: application/xml" "https://api.microsofttranslator.com/v2/http.svc/Translate?appid=Bearer%20{}&text={}&to=zh"'.format(TOKEN, query.replace(' ', '%20'))
	# print(cmd)
	system(cmd)
	print()

def main():
	'''Go through the two lists, ask microsoft, and save the result.'''
	for input_file, output_file in MT_QUERY_FILES:
		data = pd.read_csv(input_file)
		for i, query in enumerate(data['query']):
			ask_microsoft(query)

if __name__ == '__main__':
	main()
