# Sentiment Analysis

Currently test two implementations:

- Google Cloud Natural Language API

Reference: [tutorial](https://cloud.google.com/natural-language/docs/sentiment-tutorial)

## Dependency

```
pip install --upgrade google-api-python-client
```

## Usage

Modify the `SA_QUERY_FILES` list in `google.py`, then

```
export GOOGLE_APPLICATION_CREDENTIALS=<somewhere>.json
python google.py
```

- LSTM

For both deployment and test, reference the NLP project led by Johann Hauswald and Yiping Kang.
