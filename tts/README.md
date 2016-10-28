# Text-to-Speech (Voice Synthesis)

The text-to-speech service transforms a piece of text to an audio file. 
It is based on ['kaldi idlak'](https://github.com/bpotard/idlak).

# Usage

I have turned the service into a [`docker image`](`https://hub.docker.com/r/ybga/kaldi_tts/tags/`):

```
docker pull ybga/kaldi_tts
```

To use it, prepare a text file in the current directory named `transcript.txt` with one sentence each line.
Then,

```
docker run -v $PWD:/usr/local/speech ybga/kaldi_tts python -u generate_audios.py
```

which will generate audio files in the current directory.

To kill the running container,

```
docker ps
docker stop <container_id>
```
