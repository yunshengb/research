# Research

## Structure

```
asr/: automatic speech recognition
exp/: experiments
qa/: question answering
sa/: sentimental analysis
tts/: text to speech (voice synthesis)
```

## Dependency

1. [`Anaconda`](https://www.continuum.io/)

2. (optional) [`Jupyter/IPython Slideshow Extension`](https://github.com/damianavila/RISE)

```
conda install -c damianavila82 rise
```

3. (optional) [`Jupyter Themes`](https://github.com/dunovank/jupyter-themes)

```
pip install jupyterthemes
jt -l
jt -t grade3 -T -N

```

## Data Format for CSV File

1. Query should not have comma in it. For example, `"Who created Apple, Inc."`
should be converted to `"Who created Apple Inc."` or equivalent.

2. Each string field should be surrounded by double quotes. For example,
`"Hello World!","CSV file."` is good.
