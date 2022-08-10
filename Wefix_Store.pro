QT       += core gui    sql network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    buscar_produtos.cpp \
    cadastro_produtos_1.cpp \
    cadastro_produtos_2.cpp \
    cadastro_produtos_editar.cpp \
    cadastro_usuarios.cpp \
    cadastro_usuarios_2.cpp \
    janela_cadastros.cpp \
    janela_login.cpp \
    janela_suporte.cpp \
    main.cpp \
    msg_suporte.cpp \
    pdv_1.cpp \
    pdv_2.cpp \
    pdv_3.cpp \
    pdv_editar.cpp \
    relatorios.cpp \
    store.cpp \
    validar_licenca.cpp

HEADERS += \
    Conexao.h \
    buscar_produtos.h \
    cadastro_produtos_1.h \
    cadastro_produtos_2.h \
    cadastro_produtos_editar.h \
    cadastro_usuarios.h \
    cadastro_usuarios_2.h \
    get_mac_add.h \
    janela_cadastros.h \
    janela_login.h \
    janela_suporte.h \
    msg_suporte.h \
    pdv_1.h \
    pdv_2.h \
    pdv_3.h \
    pdv_editar.h \
    relatorios.h \
    store.h \
    validar_licenca.h

FORMS += \
    buscar_produtos.ui \
    cadastro_produtos_1.ui \
    cadastro_produtos_2.ui \
    cadastro_produtos_editar.ui \
    cadastro_usuarios.ui \
    cadastro_usuarios_2.ui \
    janela_cadastros.ui \
    janela_login.ui \
    janela_suporte.ui \
    msg_suporte.ui \
    pdv_1.ui \
    pdv_2.ui \
    pdv_3.ui \
    pdv_editar.ui \
    relatorios.ui \
    store.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imgs.qrc
