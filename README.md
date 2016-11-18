# Research

## Abstract

We are entering an era where large-scale AI systems with multiple service components become increasingly popular. Although many AI services can still be used in a stand-alone fashion, pipelines involving different types of AI services combined in a complex and meaningful way are both useful in the real world and interesting to the research field. For example, in order to achieve real-time cross-language communication, speech recognition is placed in a three-stage pipeline where the second stage is machine translation and the third stage is voice synthesis. Another example is a financial question-answering system that queries into banking accounts based on user's voice query. Research questions arise as such complex AI systems are built: How does the accuracy of each individual component affect the end-to-end accuracy which is the one actually experienced by users? How to combine individual components into an eco-system that enjoys easy scalability and maximum flexibility? This work analyzes the above issues and presents Lucida, an open-source AI platform, as a solution to address them.

## Structure

```
asr/: automatic speech recognition
exp/: experiments (pipelines and a tester for Lucida services)
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

3. See each directory for specific dependencies.
