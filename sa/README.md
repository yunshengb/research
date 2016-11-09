# Sentiment Analysis

Currently test two implementations:

1. Google Cloud Natural Language API

	Reference: [tutorial](https://cloud.google.com/natural-language/docs/sentiment-tutorial)

	## Dependency

	```
	pip install --upgrade google-api-python-client
	```

	## Usage

	```
	export GOOGLE_APPLICATION_CREDENTIALS=<somewhere>.json
	python google.py
	```

2. LSTM

	For both deployment and test, reference the NLP project led by Johann Hauswald and Yiping Kang.
