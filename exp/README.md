# Experiement

## Structure

```
asr_qa/: configurations and data for the (ASR -> QA) pipeline
tester/: testing framework for all the other pipelines
```

## Usage

Run each experiment in `tester/` and save the resulting data in the corresponding pipeline folder.

For example, to test the ASR -> QA pieline, 

```
cd tester
make
./X <parameters>
cd ../asr_qa
# analyze data
python analyze.py
```

Fetch the final results (graphs, text, etc.) in the pipeline folder.
