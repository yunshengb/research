# Experiement

## Structure

```
asr_qa/: configurations and data for the (ASR -> QA) pipeline
tester/: testing framework for Lucida services (Kaldi ASR, OpenEphra QA, etc.)
```

## Usage

Run each experiment in `tester/` and save the resulting data in the corresponding pipeline folder.

For example, to test the ASR -> QA pieline, 

```
cd tester
make
# Modify `config.py` which may be done multiple times, once for each service.
python run.py # test one service
# Analyze data.
# Refer to `asr_qa/`.
```

The final results (graphs, text, etc.) are in the pipeline folder.
