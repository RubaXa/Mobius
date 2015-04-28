all:
	mkdir Mobius

	cat src/List.h \
		src/Strip.h \
		src/Emitter.h \
		src/Effects.h \
		src/Pin.h \
		src/LED.h \
		src/Button.h \
		src/Motor.h \
		src/Mobius.h \
		>> Mobius/Mobius.tmp.h

	sed 's/#include/\/\/#include/' Mobius/Mobius.tmp.h > Mobius/Mobius.h
	rm Mobius/Mobius.tmp.h
	cp README.md ./Mobius
	zip -r Mobius.zip ./Mobius
	rm -rf ./Mobius
