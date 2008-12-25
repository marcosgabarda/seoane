CREATE TABLE [Articulos] (
[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,
[codigo] INTEGER  NOT NULL,
[descripcion] TEXT  NULL,
[caja] TEXT  NULL,
[existencias] INTEGER  NULL,
[existencias_minimas] INTEGER  NULL,
[pvp] REAL  NULL,
[precio_coste] REAL  NULL,
[descuento] REAL  NULL,
[historico] BOOLEAN NOT NULL DEFAULT 0
);
CREATE TABLE [Calles] (
[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,
[nombre] TEXT  NOT NULL,
[cp] INTEGER  NULL
);
CREATE TABLE [Clientes] (
[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,
[codigo] INTEGER NULL,
[nombre] TEXT  NOT NULL,
[apellidos] TEXT  NOT NULL,
[direccion] TEXT  NULL,
[nif] TEXT  NULL,
[poblacion] TEXT  NULL,
[historico] BOOLEAN NOT NULL DEFAULT 0
);
CREATE TABLE [Clientes_Callles] (
[id_cliente] INTEGER  NULL,
[id_calle] INTEGER  NULL,
PRIMARY KEY ([id_cliente],[id_calle])
);
CREATE TABLE [Facturas] (
[id] INTEGER  PRIMARY KEY AUTOINCREMENT NOT NULL,
[n_factura] INTEGER  UNIQUE NULL,
[fecha] DATE  NULL,
[aparato] TEXT  NULL,
[marca] TEXT  NULL,
[modelo] TEXT  NULL,
[n_fabricacion] TEXT  NULL,
[lugar_reparacion] BOOLEAN  NULL,
[id_cliente] INTEGER  NOT NULL,
[averia] TEXT NULL,
[trabajo_realizado] TEXT NULL,
[tiempo_empleado] TEXT NULL,
[fecha_terminacion] DATE NULL,
[observaciones] TEXT NULL,
[precio_materiales] REAL NULL,
[precio_mano_obra] REAL NULL,
[precio_desplazamiento] REAL NULL,
[precio_transporte] REAL NULL,
[iva] REAL NOT NULL
);
CREATE TABLE [Facturas_Articulos] (
[id_factura] INTEGER  NULL,
[id_articulo] INTEGER  NULL,
[cantidad] INTEGER NULL,
PRIMARY KEY ([id_factura],[id_articulo])
);
CREATE TABLE [Iva] ( [valor] INTEGER PRYMARY KEY);
CREATE TABLE [Presupuestos] (
[id] INTEGER  PRIMARY KEY AUTOINCREMENT NOT NULL,
[aceptado] BOOLEAN  NOT NULL,
[id_cliente] INTEGER  NULL,
[id_factura] INTEGER  NULL,
[n_factura] INTEGER  UNIQUE NULL,
[fecha] DATE  NULL,
[aparato] TEXT  NULL,
[marca] TEXT  NULL,
[modelo] TEXT  NULL,
[n_fabricacion] TEXT  NULL,
[lugar_reparacion] BOOLEAN  NULL,
[averia] TEXT NULL,
[trabajo_realizado] TEXT NULL,
[tiempo_empleado] TEXT NULL,
[fecha_terminacion] DATE NULL,
[observaciones] TEXT NULL,
[precio_materiales] REAL NULL,
[precio_mano_obra] REAL NULL,
[precio_desplazamiento] REAL NULL,
[precio_transporte] REAL NULL,
[iva] REAL NOT NULL
);
CREATE TABLE [Presupuestos_Articulos] (
[id_presupuesto] INTEGER  NULL,
[id_articulo] INTEGER  NULL,
[cantidad] INTEGER NULL,
PRIMARY KEY ([id_presupuesto],[id_articulo])
);
CREATE TABLE [Telefonos] (
[id] INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,
[numero] INTEGER  NOT NULL,
[id_cliente] INTEGER  NOT NULL
);
CREATE TRIGGER Unicidad_Articulos_Insert
BEFORE INSERT ON Articulos
FOR EACH ROW
	BEGIN
	SELECT CASE
	WHEN (NEW.codigo IN (SELECT codigo FROM Articulos WHERE historico=0))
	THEN raise(abort,"Violacion de unicidad en Articulos al insertar.")
	END;
END;
CREATE TRIGGER Unicidad_Articulos_Update
AFTER UPDATE ON Articulos
FOR EACH ROW
	BEGIN
	SELECT CASE
	WHEN (NEW.codigo IN (SELECT codigo FROM Articulos WHERE historico=0))
	THEN raise(abort,"Violacion de unicidad en Articulos al actualizar.")
	END;
END;
CREATE TRIGGER Unicidad_Clientes_Insert
BEFORE INSERT ON Clientes
FOR EACH ROW
	BEGIN
	SELECT CASE
	WHEN (NEW.codigo IN (SELECT codigo FROM Clientes WHERE historico=0))
	THEN raise(abort,"Violacion de unicidad en Clientes al insertar.")
	END;
END;
CREATE TRIGGER Unicidad_Clientes_Update
AFTER UPDATE ON Clientes
FOR EACH ROW
	BEGIN
	SELECT CASE
	WHEN (NEW.codigo IN (SELECT codigo FROM Clientes WHERE historico=0))
	THEN raise(abort,"Violacion de unicidad en Clientes al actualizar.")
	END;
END;
