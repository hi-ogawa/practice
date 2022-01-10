SHELL := /bin/bash
PYTHON ?= poetry run python

.PHONY: setup mypy isort black

setup:
	poetry install

mypy:
	$(PYTHON) -m mypy $(SRC)

isort:
	$(PYTHON) -m isort $(SRC)

black:
	$(PYTHON) -m black $(SRC)
