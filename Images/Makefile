.SUFFIXES: .png .inc

images.h: Kenbak.inc WhiteButton.inc WhiteButtonPressed.inc \
	BlackButton.inc BlackButtonPressed.inc \
	WhiteLightOn.inc WhiteLightOff.inc \
	YellowLightOn.inc YellowLightOff.inc
	cat *.inc > images.h

.png.inc:
	toarray $<

clean:
	-rm *.inc
	-rm images.h

