msg := new one

all: push

push:
	git add .
	git status
	git commit -m "$(msg)"
	git push
	Xiaocheng-Zhang