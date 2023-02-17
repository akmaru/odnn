# odnn: A mini DNN kernel library

## Environment setup

### Initialize .env

```sh
./docker/init_env.sh
```

### Build Docker container

```sh
docker-compose up
```

### Attach dev container

```sh
docker-compose run dev
```

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
