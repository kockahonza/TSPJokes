# TSPJokes
The repo is structured as a [Meson](https://mesonbuild.com/) project.
To build on a unix system install Meson and then run `meson setup buildir` in the repo root, `cd buildir` and `meson compile`.
(On windows get meson and build using their instructions, the `meson.build` file is in the root)
This should create a library named `TSPJokes` with the contents of the `src` folder and an executable linked with the library named `experiments` from the `main.c` file.
