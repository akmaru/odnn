# odnn: A mini DNN kernel library

## Environment setup
### Initialize .env
```sh
./docker/init_env.sh
```

### Build Docker image and attach Docker container
```sh
docker-compose up
docker-compose run dev
```

or, use VSCode devcontainer

## Build

```sh
mkdir -p build && cd build
cmake -GNinja ../
cmake --build . --parallel
```

## Test

```sh
ctest
```
