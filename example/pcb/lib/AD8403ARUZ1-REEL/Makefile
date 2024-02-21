ZIP = LIB_AD8403ARUZ1-REEL.zip
URL = https://componentsearchengine.com/part-view/AD8403ARUZ1-REEL/Analog%20Devices

TMP = tmp
TMP_DIR = $(TMP)/AD8403ARUZ1-REEL
TMP_KICAD = $(TMP_DIR)/KiCad
TMP_3D = $(TMP_DIR)/3D

KICAD_MOD_SRC = $(TMP_KICAD)/SOP65P640X120-24N.kicad_mod
KICAD_SYM_SRC = $(TMP_KICAD)/AD8403ARUZ1-REEL.kicad_sym
STP_SRC = $(TMP_3D)/AD8403ARUZ1-REEL.stp

KICAD_PRETTY = AD8403ARUZ1-REEL.pretty
KICAD_MOD = $(KICAD_PRETTY)/SOP65P640X120-24N.kicad_mod
KICAD_SYM = AD8403ARUZ1-REEL.kicad_sym
STP = AD8403ARUZ1-REEL.stp

SRC = $(KICAD_MOD_SRC) $(KICAD_SYM_SRC) $(STP_SRC)
DEST = $(KICAD_PRETTY) $(KICAD_MOD) $(KICAD_SYM) $(STP)

.PHONY: all clean

all: $(DEST)

clean:
	rm -rf $(TMP) $(DEST)

$(ZIP):
	@if [ ! -f $@ ]; then \
		echo "Download $@ from $(URL)"; \
		exit 1; \
	fi

$(TMP): $(ZIP)
	unzip -o $< -d $@

$(SRC): | $(TMP)
	@if [ ! -f $@ ]; then \
		echo "$@ not found. $(ZIP) may be updated."; \
		exit 1; \
	fi

$(KICAD_PRETTY):
	mkdir $@

$(KICAD_MOD): $(KICAD_MOD_SRC) $(KICAD_PRETTY)
	cp $< $@

$(KICAD_SYM): $(KICAD_SYM_SRC)
	cp $< $@

$(STP): $(STP_SRC)
	cp $< $@
