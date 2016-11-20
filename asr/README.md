# Automatic Speech Recognition

Currently test one implementation:

## Kaldi

On the server directory `lucida/tools/deploy`, to pre-process the Kubernetes scripts and start the cluster,

```
git pull origin master
mv asrworker-controller-https.yaml asrworker-controller.yaml
mv asrmaster-controller-https.yaml asrmaster-controller.yaml
mv web-controller-https.yaml web-controller.yaml
mv web-service-https.yaml web-service.yaml
sudo ./cluster_up.sh

```

To re-start the services,

```
sudo ./start_services.sh
```

## Evaluation: Word Error Rate (WER)

## Usgae

```
python wer.py
```

Or import `error_rate` from another Python script.

