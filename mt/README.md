# Machine Translation

Currently test two implementations:

## Google Translation API

Reference: [API](https://developers.google.com/api-client-library/python/apis/translate/v2)

### Dependency

```
pip install --upgrade google-api-python-client
```

### Usage

Modify the file list in `google.py`, then

```
export developerKey=<some_key>
python google.py
```

## Microsoft Translation API

Reference: [this](http://docs.microsofttranslator.com/text-translate.html)
for registration, key access, and POST format, and
[this](http://docs.microsofttranslator.com/oauth-token.html) for obtaining a token using the key.
`Each token is good for ten minutes,` so if experiment is longer than ten minutes,
modify the code so that it automatically obtains the token once the time is up.

## Usage

Modify the file list and the `TOKEN` in `microsoft.py`, then

```
python microsoft.py > microsoft_temp.txt # hacky due to a unicode problem using `checkout_output`
python process_microsoft_temp_result.py # parse the microsoft_temp.txt generated above
```

## Evaluation: BLEU

To evaluate the translation result, we can use the BLEU matric.

## Dependency

```
sudo pip install -U nltk
wget http://nlp.stanford.edu/software/stanford-segmenter-2015-12-09.zip # 255 MB
tar xvzf stanford-segmenter-2015-12-09.zip
mv stanford-segmenter-2015-12-09.zip segmenter
```

## Usgae

```
python bleu.py
```

Or import `bleu` and use the `Evaluator` object from another Python script.
