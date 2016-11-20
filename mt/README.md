# Machine Translation

Currently test one implementation:

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
