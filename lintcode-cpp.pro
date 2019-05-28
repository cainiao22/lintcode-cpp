QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    repeated-substring-pattern.cpp \
    process-sequence.cpp \
    paper-review.cpp \
    the-longest-scene.cpp \
    segment-stones-merge.cpp \
    permutations.cpp \
    monotone-increasing-digits.cpp \
    binary-tree-zigzag-level-order-traversal.cpp \
    champagne-tower.cpp \
    binary-tree-maximum-path-sum.cpp \
    squirrel-simulation.cpp \
    the-skyline-problem.cpp \
    update-bits.cpp \
    count-numbers-with-unique-digits.cpp \
    integer-replacement.cpp \
    wiggle-subsequence.cpp \
    optimal-division.cpp \
    repeated-dna-sequences.cpp \
    is-graph-bipartite.cpp \
    minimum-number-of-arrows-to-burst-balloons.cpp \
    target-sum.cpp \
    ternary-expression-parser.cpp \
    sort-colors.cpp \
    find-k-closest-elements.cpp \
    create-maximum-number.cpp \
    pacific-atlantic-water-flow.cpp \
    asteroid-collision.cpp \
    commonutils.cpp \
    gray-code.cpp \
    contiguous-array.cpp \
    strong-password-checke.cpp \
    longest-substring-without-repeating-characters.cpp \
    rabbits-in-forest.cpp \
    gas-station.cpp \
    sort-list.cpp \
    zuma-game.cpp \
    subsets.cpp \
    3sum.cpp \
    minimum-window-substring.cpp \
    candy.cpp \
    all-paths-from-source-to-target.cpp \
    linked-list-cycle.cpp \
    n-queens.cpp \
    interleaving-string.cpp \
    graph-valid-tree.cpp \
    merge-number.cpp \
    longest-increasing-subsequence.cpp \
    longest-palindromic-substring.cpp \
    paint-house.cpp \
    binary-tree-level-order-traversal-ii.cpp \
    network-delay-time.cpp \
    remove-boxes.cpp \
    candy-crush.cpp \
    and-and-or.cpp \
    bus-routes.cpp \
    circular-array-loop.cpp \
    2-keys-keyboard.cpp \
    pour-water.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    commonutils.h
