 #include <QtGui>
 #include "ventana.h"

Ventana::~Ventana() {
    delete visorOpenGL;
}

Ventana::Ventana() {
    setWindowTitle(tr("QTron. Miguel Cantón Cortés"));

    visorOpenGL = new VisorOpenGL;
    setCentralWidget(visorOpenGL);

    crearMenu();
}

void Ventana::crearMenu() {
    Juego = menuBar()->addMenu(tr("&Juego"));
        nuevoJuego = new QAction(tr("&Empezar partida nueva"), this);
        nuevoJuego->setStatusTip(tr("Empezar partida nueva"));
        connect(nuevoJuego, SIGNAL(triggered()), this, SLOT(empezarPartida()));
        Juego->addAction(nuevoJuego);

        pausar = new QAction(tr("&Pausar partida"), this);
        pausar->setStatusTip(tr("Pausar partida"));
        connect(pausar, SIGNAL(triggered()), this, SLOT(pausarPartida()));
        Juego->addAction(pausar);

        terminar = new QAction(tr("&Finalizar Partida"), this);
        terminar->setStatusTip(tr("Finalizar Partida"));
        connect(terminar, SIGNAL(triggered()), this, SLOT(terminarPartida()));
        Juego->addAction(terminar);

        Juego->addSeparator();

        salir = new QAction(tr("&Salir"), this);
        salir->setStatusTip(tr("Salir"));
        connect(salir, SIGNAL(triggered()), this, SLOT(close()));
        Juego->addAction(salir);

    Opciones = menuBar()->addMenu(tr("&Opciones"));
        NJugadores = new QAction(tr("&Elegir número de jugadores"), this);
        NJugadores->setStatusTip(tr("Elegir número de jugadores"));
        connect(NJugadores, SIGNAL(triggered()), this, SLOT(elegirNJugadores()));
        Opciones->addAction(NJugadores);

        TamTablero = new QAction(tr("&Elegir el tamaño del tablero"), this);
        TamTablero->setStatusTip(tr("Elegir el tamaño del tablero"));
        connect(TamTablero, SIGNAL(triggered()), this, SLOT(elegirTamTablero()));
        Opciones->addAction(TamTablero);

        Velocidad = new QAction(tr("&Elegir velocidad de las motos"), this);
        Velocidad->setStatusTip(tr("Elegir velocidad de las motos"));
        connect(Velocidad, SIGNAL(triggered()), this, SLOT(setVelocidad()));
        Opciones->addAction(Velocidad);

    ModosVisualizacion = menuBar()->addMenu(tr("&Modos de Visualización"));
        Reflejos = new QAction(tr("&Activar/Desactivar reflejos"), this);
        Reflejos->setStatusTip(tr("Activar/Desactivar reflejos"));
        connect(Reflejos, SIGNAL(triggered()), this, SLOT(elegirReflejos()));
        ModosVisualizacion->addAction(Reflejos);

        Ejes = new QAction(tr("&Mostrar/Ocultar ejes"), this);
        Ejes->setStatusTip(tr("Mostrar/Ocultar ejes"));
        connect(Ejes, SIGNAL(triggered()), this, SLOT(elegirEjes()));
        ModosVisualizacion->addAction(Ejes);

        ModosVisualizacion->addSeparator();

        CamaraLibre = new QAction(tr("&Cámara Libre"), this);
        CamaraLibre->setStatusTip(tr("Cámara Libre"));
        connect(CamaraLibre, SIGNAL(triggered()), this, SLOT(setCamaraLibre()));
        ModosVisualizacion->addAction(CamaraLibre);

        ModosVisualizacion->addSeparator();

        Puntos = new QAction(tr("&Puntos"), this);
        Puntos->setStatusTip(tr("Puntos"));
        connect(Puntos, SIGNAL(triggered()), this, SLOT(modoPuntos()));
        ModosVisualizacion->addAction(Puntos);

        Lineas = new QAction(tr("&Lineas"), this);
        Lineas->setStatusTip(tr("Lineas"));
        connect(Lineas, SIGNAL(triggered()), this, SLOT(modoLineas()));
        ModosVisualizacion->addAction(Lineas);

        Solido = new QAction(tr("&Solido"), this);
        Solido->setStatusTip(tr("Solido"));
        connect(Solido, SIGNAL(triggered()), this, SLOT(modoSolido()));
        ModosVisualizacion->addAction(Solido);

        Ajedrez = new QAction(tr("&Ajedrez"), this);
        Ajedrez->setStatusTip(tr("Ajedrez"));
        connect(Ajedrez, SIGNAL(triggered()), this, SLOT(modoAjedrez()));
        ModosVisualizacion->addAction(Ajedrez);

        this->Flat = new QAction(tr("&Suavizado Flat"), this);
        this->Flat->setStatusTip(tr("Suavizado Flat"));
        connect(this->Flat, SIGNAL(triggered()), this, SLOT(modoFlat()));
        ModosVisualizacion->addAction(this->Flat);

        Smooth = new QAction(tr("&Suavizado Smooth"), this);
        Smooth->setStatusTip(tr("Suavizado Smooth"));
        connect(Smooth, SIGNAL(triggered()), this, SLOT(modoSmooth()));
        ModosVisualizacion->addAction(Smooth);

    fullScreen = menuBar()->addMenu(tr("&Pantalla"));
        pantCompleta = new QAction(tr("&Completa"), this);
        pantCompleta->setStatusTip(tr("Completa"));
        connect(pantCompleta, SIGNAL(triggered()), this, SLOT(showFullScreen()));
        fullScreen->addAction(pantCompleta);

        pantNormal = new QAction(tr("&Ventana"), this);
        pantNormal->setStatusTip(tr("Ventana"));
        connect(pantNormal, SIGNAL(triggered()), this, SLOT(showNormal()));
        fullScreen->addAction(pantNormal);

    Extra = menuBar()->addMenu(tr("&Extra"));
        Ayuda = new QAction(tr("&Ayuda"), this);
        Ayuda->setStatusTip(tr("Ayuda"));
        connect(Ayuda, SIGNAL(triggered()), this, SLOT(showAyuda()));
        Extra->addAction(Ayuda);

        Acerca = new QAction(tr("&Acerca"), this);
        Acerca->setStatusTip(tr("Acerca"));
        connect(Acerca, SIGNAL(triggered()), this, SLOT(showAcerca()));
        Extra->addAction(Acerca);

        Extra->addSeparator();

        Demo = new QAction(tr("&Demo"), this);
        Demo->setStatusTip(tr("Demo"));
        connect(Demo, SIGNAL(triggered()), this, SLOT(showDemo()));
        Extra->addAction(Demo);
}

void Ventana::empezarPartida() {
    visorOpenGL->setModo(JUEGO);
    visorOpenGL->juego.iniciarPartida();
}
void Ventana::pausarPartida() {
    visorOpenGL->juego.pausarPartida();
}
void Ventana::terminarPartida() {
    visorOpenGL->setModo(MENU);
}

void Ventana::elegirNJugadores() {
    bool ok;
    int i = QInputDialog::getInteger(this, tr("Número de Jugadores"),tr("Número:"), 2, 1, 8, 1, &ok);
    if(ok)
        visorOpenGL->juego.setNumeroMotos(i);
}
void Ventana::elegirTamTablero() {
    bool ok;
    int i = QInputDialog::getInteger(this, tr("Tamaño de tablero"),tr("Tamaño:"), 300, 100, 1000, 10, &ok);
    if(ok)
        visorOpenGL->juego.setTamanoTablero(i);
}
void Ventana::setVelocidad() {
    bool ok;
    int i = QInputDialog::getInteger(this, tr("Velocidad de las motos"),tr("Velocidad:"), 3, 1, 10, 1, &ok);
    if(ok)
        visorOpenGL->juego.motos.setVelocidadMotos(i/10.0);
}

void Ventana::elegirReflejos() {
    QStringList opciones;
    opciones << tr("Activar Reflejos") << tr("Desactivar Reflejos");
    bool ok;
    QString item = QInputDialog::getItem(this, tr("Opciones"),tr("Elección:"), opciones, 0, false, &ok);
    if(ok && !item.isEmpty())
        visorOpenGL->juego.setReflejos(item == tr("Activar Reflejos"));
}
void Ventana::elegirEjes() {
    QStringList opciones;
    opciones << tr("Mostrar Ejes") << tr("Ocultar Ejes");
    bool ok;
    QString item = QInputDialog::getItem(this, tr("Opciones"),tr("Elección:"), opciones, 0, false, &ok);
    if(ok && !item.isEmpty())
        visorOpenGL->juego.setEjes(item == tr("Mostrar Ejes"));
}

void Ventana::modoPuntos() {
    visorOpenGL->juego.setModoDibujo(0);
    visorOpenGL->demo.setModoDibujo(0);
}
void Ventana::modoLineas() {
    visorOpenGL->juego.setModoDibujo(1);
    visorOpenGL->demo.setModoDibujo(1);
}
void Ventana::modoSolido() {
    visorOpenGL->juego.setModoDibujo(2);
    visorOpenGL->demo.setModoDibujo(2);
}
void Ventana::modoAjedrez() {
    visorOpenGL->juego.setModoDibujo(3);
    visorOpenGL->demo.setModoDibujo(3);
}
void Ventana::modoFlat() {
    visorOpenGL->juego.setModoDibujo(4);
    visorOpenGL->juego.setModoSuavizado(GL_FLAT);
    visorOpenGL->demo.setModoDibujo(4);
    visorOpenGL->demo.setModoSuavizado(GL_FLAT);
}
void Ventana::modoSmooth() {
    visorOpenGL->juego.setModoDibujo(4);
    visorOpenGL->juego.setModoSuavizado(GL_SMOOTH);
    visorOpenGL->demo.setModoDibujo(4);
    visorOpenGL->demo.setModoSuavizado(GL_SMOOTH);
}
void Ventana::setCamaraLibre() {
    QStringList opciones;
    opciones << tr("Activar") << tr("Desactivar") << "" << tr("Configurar cámara nueva");
    bool ok;
    QString item = QInputDialog::getItem(this, tr("Cámara Libre"),tr("Elección:"), opciones, 0, false, &ok);
    if(ok && !item.isEmpty()) {
        visorOpenGL->juego.setCamaraLibre(item == tr("Activar"));
        if(item == tr("Configurar cámara nueva")) {
            Vertice VRP;
            Vertice VPN;
            Vertice VUP;
            VRP.x = QInputDialog::getDouble(this, tr("Configurar cámara nueva"),tr("VRP.x:"), -15, -150, 150, 0.5, &ok);
            if(!ok) return;
            VRP.y = QInputDialog::getDouble(this, tr("Configurar cámara nueva"),tr("VRP.y:"), 10, -150, 150, 0.5, &ok);
            if(!ok) return;
            VRP.z = QInputDialog::getDouble(this, tr("Configurar cámara nueva"),tr("VRP.z:"), -20, -150, 150, 0.5, &ok);
            if(!ok) return;
            VPN.x = QInputDialog::getDouble(this, tr("Configurar cámara nueva"),tr("VPN.x:"), 0, -150, 150, 0.5, &ok);
            if(!ok) return;
            VPN.y = QInputDialog::getDouble(this, tr("Configurar cámara nueva"),tr("VPN.y:"), 0.5, -150, 150, 0.5, &ok);
            if(!ok) return;
            VPN.z = QInputDialog::getDouble(this, tr("Configurar cámara nueva"),tr("VPN.z:"), -1, -150, 150, 0.5, &ok);
            if(!ok) return;
            VUP.x = QInputDialog::getDouble(this, tr("Configurar cámara nueva"),tr("VUP.x:"), 0, -150, 150, 0.5, &ok);
            if(!ok) return;
            VUP.y = QInputDialog::getDouble(this, tr("Configurar cámara nueva"),tr("VUP.y:"), 1, -150, 150, 0.5, &ok);
            if(!ok) return;
            VUP.z = QInputDialog::getDouble(this, tr("Configurar cámara nueva"),tr("VUP.z:"), 0, -150, 150, 0.5, &ok);
            if(!ok) return;
            visorOpenGL->demo.camara.configurarCamara(VRP, VPN, VUP);
            visorOpenGL->juego.camaraLibre.configurarCamara(VRP, VPN, VUP);
            visorOpenGL->juego.setCamaraLibre(true);
        }
    }
}

void Ventana::showAcerca() {
    QMessageBox msgBox;
    QString mensaje = QString("Juego creado por Miguel Cantón Cortés. (Informática Gráfica, 2011)        ");
    msgBox.setText(mensaje);
    msgBox.setWindowTitle("Acerca");
    msgBox.exec();
}
void Ventana::showAyuda() {
    QMessageBox msgBox;
    QString mensaje = QString("Mostrando ayuda...");

    visorOpenGL->menu.showAyuda();
    visorOpenGL->setModo(MENU);
    msgBox.setText(mensaje);
    msgBox.setWindowTitle("Ayuda");
    msgBox.exec();
    visorOpenGL->menu.showFondo();
}
void Ventana::showDemo() {
    QStringList opciones;
    opciones << tr("Figuras") << tr("Hormigas");
    bool ok;
    QString item = QInputDialog::getItem(this, tr("Modo Demo"),tr("Modo:"), opciones, 0, false, &ok);
    if(ok && !item.isEmpty()) {
        if(item == tr("Figuras"))
            visorOpenGL->demo.setModoDemo(FIGURAS);
        else
            visorOpenGL->demo.setModoDemo(HORMIGAS);
        visorOpenGL->setModo(DEMO);
    }
}
