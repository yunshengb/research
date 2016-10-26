# Pipeline Tester

## Compilation

```
make
```

Since the cpp program does not depend on anything other than the standard library and `libcurl` (i.e. no `boost`, `glog`, etc.),
you should be able to compile it even on OS X. 

## Run

To test a pipeline, modify the `config.py` and run `python run.py`.
It starts the cpp program automatically.

To directly interact with the cpp program, run `make && ./X`.
