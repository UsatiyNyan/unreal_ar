gst-launch-1.0 -v udpsrc port=$1 \
! application/x-rtp, media=video, clock-rate=90000, encoding-name=JPEG, payload=26 \
! rtpjpegdepay \
! jpegdec \
! xvimagesink sync=0
