QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../../../../../Downloads/TasksQ/iconsressources.qrc
QT += charts
DISTFILES += \
    ../../icon/activity.svg \
    ../../icon/airplay.svg \
    ../../icon/alert-circle.svg \
    ../../icon/alert-octagon.svg \
    ../../icon/alert-triangle.svg \
    ../../icon/align-center.svg \
    ../../icon/align-justify.svg \
    ../../icon/align-left.svg \
    ../../icon/align-right.svg \
    ../../icon/anchor.svg \
    ../../icon/aperture.svg \
    ../../icon/archive.svg \
    ../../icon/arrow-down-circle.svg \
    ../../icon/arrow-down-left.svg \
    ../../icon/arrow-down-right.svg \
    ../../icon/arrow-down.svg \
    ../../icon/arrow-left-circle.svg \
    ../../icon/arrow-left.svg \
    ../../icon/arrow-right-circle.svg \
    ../../icon/arrow-right.svg \
    ../../icon/arrow-up-circle.svg \
    ../../icon/arrow-up-left.svg \
    ../../icon/arrow-up-right.svg \
    ../../icon/arrow-up.svg \
    ../../icon/at-sign.svg \
    ../../icon/award.svg \
    ../../icon/bar-chart-2.svg \
    ../../icon/bar-chart.svg \
    ../../icon/battery-charging.svg \
    ../../icon/battery.svg \
    ../../icon/bell-off.svg \
    ../../icon/bell.svg \
    ../../icon/bluetooth.svg \
    ../../icon/bold.svg \
    ../../icon/book-open.svg \
    ../../icon/book.svg \
    ../../icon/bookmark.svg \
    ../../icon/box.svg \
    ../../icon/briefcase.svg \
    ../../icon/calendar.svg \
    ../../icon/camera-off.svg \
    ../../icon/camera.svg \
    ../../icon/cast.svg \
    ../../icon/check-circle.svg \
    ../../icon/check-square.svg \
    ../../icon/check.svg \
    ../../icon/chevron-down.svg \
    ../../icon/chevron-left.svg \
    ../../icon/chevron-right.svg \
    ../../icon/chevron-up.svg \
    ../../icon/chevrons-down.svg \
    ../../icon/chevrons-left.svg \
    ../../icon/chevrons-right.svg \
    ../../icon/chevrons-up.svg \
    ../../icon/chrome.svg \
    ../../icon/circle.svg \
    ../../icon/clipboard.svg \
    ../../icon/clock.svg \
    ../../icon/cloud-drizzle.svg \
    ../../icon/cloud-lightning.svg \
    ../../icon/cloud-off.svg \
    ../../icon/cloud-rain.svg \
    ../../icon/cloud-snow.svg \
    ../../icon/cloud.svg \
    ../../icon/code.svg \
    ../../icon/codepen.svg \
    ../../icon/codesandbox.svg \
    ../../icon/coffee.svg \
    ../../icon/columns.svg \
    ../../icon/command.svg \
    ../../icon/compass.svg \
    ../../icon/copy.svg \
    ../../icon/corner-down-left.svg \
    ../../icon/corner-down-right.svg \
    ../../icon/corner-left-down.svg \
    ../../icon/corner-left-up.svg \
    ../../icon/corner-right-down.svg \
    ../../icon/corner-right-up.svg \
    ../../icon/corner-up-left.svg \
    ../../icon/corner-up-right.svg \
    ../../icon/cpu.svg \
    ../../icon/credit-card.svg \
    ../../icon/crop.svg \
    ../../icon/crosshair.svg \
    ../../icon/database.svg \
    ../../icon/delete.svg \
    ../../icon/disc.svg \
    ../../icon/divide-circle.svg \
    ../../icon/divide-square.svg \
    ../../icon/divide.svg \
    ../../icon/dollar-sign.svg \
    ../../icon/download-cloud.svg \
    ../../icon/download.svg \
    ../../icon/dribbble.svg \
    ../../icon/droplet.svg \
    ../../icon/edit-2.svg \
    ../../icon/edit-3.svg \
    ../../icon/edit.svg \
    ../../icon/external-link.svg \
    ../../icon/eye-off.svg \
    ../../icon/eye.svg \
    ../../icon/facebook.svg \
    ../../icon/fast-forward.svg \
    ../../icon/feather.svg \
    ../../icon/figma.svg \
    ../../icon/file-minus.svg \
    ../../icon/file-plus.svg \
    ../../icon/file-text.svg \
    ../../icon/file.svg \
    ../../icon/film.svg \
    ../../icon/filter.svg \
    ../../icon/flag.svg \
    ../../icon/folder-minus.svg \
    ../../icon/folder-plus.svg \
    ../../icon/folder.svg \
    ../../icon/framer.svg \
    ../../icon/frown.svg \
    ../../icon/gift.svg \
    ../../icon/git-branch.svg \
    ../../icon/git-commit.svg \
    ../../icon/git-merge.svg \
    ../../icon/git-pull-request.svg \
    ../../icon/github.svg \
    ../../icon/gitlab.svg \
    ../../icon/globe.svg \
    ../../icon/grid.svg \
    ../../icon/hard-drive.svg \
    ../../icon/hash.svg \
    ../../icon/headphones.svg \
    ../../icon/heart.svg \
    ../../icon/help-circle.svg \
    ../../icon/hexagon.svg \
    ../../icon/home.svg \
    ../../icon/image.svg \
    ../../icon/inbox.svg \
    ../../icon/info.svg \
    ../../icon/instagram.svg \
    ../../icon/italic.svg \
    ../../icon/key.svg \
    ../../icon/layers.svg \
    ../../icon/layout.svg \
    ../../icon/life-buoy.svg \
    ../../icon/link-2.svg \
    ../../icon/link.svg \
    ../../icon/linkedin.svg \
    ../../icon/list.svg \
    ../../icon/loader.svg \
    ../../icon/lock.svg \
    ../../icon/log-in.svg \
    ../../icon/log-out.svg \
    ../../icon/mail.svg \
    ../../icon/map-pin.svg \
    ../../icon/map.svg \
    ../../icon/maximize-2.svg \
    ../../icon/maximize.svg \
    ../../icon/meh.svg \
    ../../icon/menu.svg \
    ../../icon/message-circle.svg \
    ../../icon/message-square.svg \
    ../../icon/mic-off.svg \
    ../../icon/mic.svg \
    ../../icon/minimize-2.svg \
    ../../icon/minimize.svg \
    ../../icon/minus-circle.svg \
    ../../icon/minus-square.svg \
    ../../icon/minus.svg \
    ../../icon/monitor.svg \
    ../../icon/moon.svg \
    ../../icon/more-horizontal.svg \
    ../../icon/more-vertical.svg \
    ../../icon/mouse-pointer.svg \
    ../../icon/move.svg \
    ../../icon/music.svg \
    ../../icon/navigation-2.svg \
    ../../icon/navigation.svg \
    ../../icon/octagon.svg \
    ../../icon/package.svg \
    ../../icon/paperclip.svg \
    ../../icon/pause-circle.svg \
    ../../icon/pause.svg \
    ../../icon/pen-tool.svg \
    ../../icon/percent.svg \
    ../../icon/phone-call.svg \
    ../../icon/phone-forwarded.svg \
    ../../icon/phone-incoming.svg \
    ../../icon/phone-missed.svg \
    ../../icon/phone-off.svg \
    ../../icon/phone-outgoing.svg \
    ../../icon/phone.svg \
    ../../icon/pie-chart.svg \
    ../../icon/play-circle.svg \
    ../../icon/play.svg \
    ../../icon/plus-circle.svg \
    ../../icon/plus-square.svg \
    ../../icon/plus.svg \
    ../../icon/pocket.svg \
    ../../icon/power.svg \
    ../../icon/printer.svg \
    ../../icon/radio.svg \
    ../../icon/refresh-ccw.svg \
    ../../icon/refresh-cw.svg \
    ../../icon/repeat.svg \
    ../../icon/rewind.svg \
    ../../icon/rotate-ccw.svg \
    ../../icon/rotate-cw.svg \
    ../../icon/rss.svg \
    ../../icon/save.svg \
    ../../icon/scissors.svg \
    ../../icon/search.svg \
    ../../icon/send.svg \
    ../../icon/server.svg \
    ../../icon/settings.svg \
    ../../icon/share-2.svg \
    ../../icon/share.svg \
    ../../icon/shield-off.svg \
    ../../icon/shield.svg \
    ../../icon/shopping-bag.svg \
    ../../icon/shopping-cart.svg \
    ../../icon/shuffle.svg \
    ../../icon/sidebar.svg \
    ../../icon/skip-back.svg \
    ../../icon/skip-forward.svg \
    ../../icon/slack.svg \
    ../../icon/slash.svg \
    ../../icon/sliders.svg \
    ../../icon/smartphone.svg \
    ../../icon/smile.svg \
    ../../icon/speaker.svg \
    ../../icon/square.svg \
    ../../icon/star.svg \
    ../../icon/stop-circle.svg \
    ../../icon/sun.svg \
    ../../icon/sunrise.svg \
    ../../icon/sunset.svg \
    ../../icon/table.svg \
    ../../icon/tablet.svg \
    ../../icon/tag.svg \
    ../../icon/target.svg \
    ../../icon/terminal.svg \
    ../../icon/thermometer.svg \
    ../../icon/thumbs-down.svg \
    ../../icon/thumbs-up.svg \
    ../../icon/toggle-left.svg \
    ../../icon/toggle-right.svg \
    ../../icon/tool.svg \
    ../../icon/trash-2.svg \
    ../../icon/trash.svg \
    ../../icon/trello.svg \
    ../../icon/trending-down.svg \
    ../../icon/trending-up.svg \
    ../../icon/triangle.svg \
    ../../icon/truck.svg \
    ../../icon/tv.svg \
    ../../icon/twitch.svg \
    ../../icon/twitter.svg \
    ../../icon/type.svg \
    ../../icon/umbrella.svg \
    ../../icon/underline.svg \
    ../../icon/unlock.svg \
    ../../icon/upload-cloud.svg \
    ../../icon/upload.svg \
    ../../icon/user-check.svg \
    ../../icon/user-minus.svg \
    ../../icon/user-plus.svg \
    ../../icon/user-x.svg \
    ../../icon/user.svg \
    ../../icon/users.svg \
    ../../icon/video-off.svg \
    ../../icon/video.svg \
    ../../icon/voicemail.svg \
    ../../icon/volume-1.svg \
    ../../icon/volume-2.svg \
    ../../icon/volume-x.svg \
    ../../icon/volume.svg \
    ../../icon/watch.svg \
    ../../icon/wifi-off.svg \
    ../../icon/wifi.svg \
    ../../icon/wind.svg \
    ../../icon/x-circle.svg \
    ../../icon/x-octagon.svg \
    ../../icon/x-square.svg \
    ../../icon/x.svg \
    ../../icon/youtube.svg \
    ../../icon/zap-off.svg \
    ../../icon/zap.svg \
    ../../icon/zoom-in.svg \
    ../../icon/zoom-out.svg
