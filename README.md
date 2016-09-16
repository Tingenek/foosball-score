# Foosball-score

![Alt text](https://cloud.githubusercontent.com/assets/1476541/18579986/da73059e-7bf0-11e6-975c-9378f2495329.jpg)

IR + Arduino + RPi + MQTT Foosball table goal system.

This is a loosly coupled foosball score system. Since I couldn't use WiFi, it's a bit more long winded. The system consists of:

1) A re-purposed Tilda E badge from EMFCamp 2014
https://badge.emfcamp.org/wiki/TiLDA_MKe
This is a Arduino Due with a small screen, battery and an SRF radio. I
could have used a Ciseco RFU328 but this was handy and came with
battery/screen etc. It shows scores locally and also sends them via SRF
Radio to:

2) An RPi. This is because I have to have a wired LAN connection. The PI
sends out the scores to iot.eclipse.org via MQTT using my favorite Apache Camel.

3) Something interesting to pick up the scores... TBD

4) (Optional) 125KHz RFID reader so playes can 'log-in' with their badges.
