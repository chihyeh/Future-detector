###############################################################################
#
# Makefile for the photon note
#                              	
###############################################################################

NOTENAME=fcc_hcal

all:#default target makes everything
	latex $(NOTENAME).tex && bibtex $(NOTENAME) && latex $(NOTENAME).tex && latex $(NOTENAME).tex && dvips -Ppdf -G0 $(NOTENAME).dvi && ps2pdf $(NOTENAME).ps

show:
	ps2pdf $(NOTENAME).ps && evince $(NOTENAME).pdf

.PHONY: clean
clean:
	rm -rf $(NOTENAME).aux $(NOTENAME).log $(NOTENAME).dvi $(NOTENAME).out $(NOTENAME).bbl $(NOTENAME).blg\
	$(NOTENAME).dvi $(NOTENAME).ps \
	$(NOTENAME).toc $(NOTENAME).tof thumb*.* *~ 
	rm $(NOTENAME).pdf
