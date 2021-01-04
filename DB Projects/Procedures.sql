use Filme
go

CREATE TABLE DatabaseVersion
(
	version INT
);

INSERT INTO DatabaseVersion(version) VALUES
(0)

UPDATE DatabaseVersion
SET version = 0;

SELECT version FROM DatabaseVersion

CREATE PROCEDURE procedura1
AS
BEGIN
	ALTER TABLE Filme
	ALTER COLUMN numeFilm VARCHAR(100)

	PRINT 'S-a modificat cu succes tipul coloanei numeFilm in VARCHAR(100) din tabela Filme!'

	UPDATE DatabaseVersion
	SET version = 1;
END;

DROP PROCEDURE undoprocedura5

EXEC procedura1;

CREATE PROCEDURE undoprocedura1
AS
BEGIN
	ALTER TABLE Filme
	ALTER COLUMN numeFilm VARCHAR(50)

	PRINT 'S-a modificat cu succes tipul coloanei numeFilm in VARCHAR(50) din tabela Filme!'

	UPDATE DatabaseVersion
	SET version = 0;
END;

EXEC undoprocedura1;

CREATE PROCEDURE procedura2
AS
BEGIN
	ALTER TABLE Proiectii
	ADD CONSTRAINT suportDf DEFAULT 'NU' for suport4D

	PRINT 'S-a adaugat cu succes constrangerea de valoare implicita "NU" pentru campul suport4D din Proiectii!'

	UPDATE DatabaseVersion
	SET version = 2;
END;

EXEC procedura2;

CREATE PROCEDURE undoprocedura2
AS
BEGIN
	ALTER TABLE Proiectii
	DROP CONSTRAINT suportDf

	PRINT 'S-a sters cu succes constrangerea de valoare implicita "NU" pentru campul suport4D din Proiectii!'

	UPDATE DatabaseVersion
	SET version = 1;
END;

EXEC undoprocedura2;

CREATE PROCEDURE procedura3
AS
BEGIN
	CREATE TABLE Vizionari
	(
	idVizionare INT PRIMARY KEY,
	numeCinema VARCHAR(50),
	numeFilm VARCHAR(50),
	numarVizionari INT
	);

	PRINT 'S-a creat cu succes tabela Vizionari!'

	UPDATE DatabaseVersion
	SET version = 3;
END;

EXEC procedura3;

CREATE PROCEDURE undoprocedura3
AS
BEGIN
	DROP TABLE Vizionari

	PRINT 'S-a sters cu succes tabela Vizionari!'

	UPDATE DatabaseVersion
	SET version = 2;
END;

EXEC undoprocedura3;

CREATE PROCEDURE procedura4
AS
BEGIN
	ALTER TABLE Cinema
	ADD judet VARCHAR(50)

	PRINT 'S-a adaugat cu succes noul camp judet in tabela Cinema!'

	UPDATE DatabaseVersion
	SET version = 4;
END;

EXEC procedura4;

CREATE PROCEDURE undoprocedura4
AS
BEGIN
	ALTER TABLE Cinema
	DROP COLUMN judet

	PRINT 'S-a sters cu succes campul judet din tabela Cinema!'

	UPDATE DatabaseVersion
	SET version = 3;
END;

EXEC undoprocedura4;

CREATE PROCEDURE procedura5
AS
BEGIN
	ALTER TABLE Vizionari
	ADD CONSTRAINT idForeignK FOREIGN KEY(idVizionare) REFERENCES Proiectii(idProiectie)

	PRINT 'S-a creat cu succes constrangerea de cheie straina idForeignK pentru idVizionare din Vizionari!'

	UPDATE DatabaseVersion
	SET version = 5;
END;

EXEC procedura5;

CREATE PROCEDURE undoprocedura5
AS
BEGIN
	ALTER TABLE Vizionari
	DROP CONSTRAINT idForeignK

	PRINT 'S-a sters cu succes constrangerea de cheie straina idForeignK pentru idVizionare din Vizionari!'

	UPDATE DatabaseVersion
	SET version = 4;
END;

EXEC undoprocedura5;

CREATE PROCEDURE main
@versiune INT
AS
BEGIN
	DECLARE @ok INT
	SET @ok = 1

	IF ISNUMERIC(@versiune) = 0
	BEGIN
		RAISERROR('Versiunea trebuie sa fie un numar intreg!',10,1);
		SET @ok = 0
	END
	IF @ok = 1
		BEGIN
			IF ISNULL(@versiune,10) = 10
				BEGIN
					RAISERROR('Versiunea trebuie sa fie nenula!',10,1);
					SET @ok = 0
				END
		END
	IF @ok = 1
	BEGIN
		IF @versiune>5 AND @versiune<0
			BEGIN
				RAISERROR('Versiunea trebuie sa fie <= 5!',10,1);
				SET @ok = 0
			END
	END

	IF @ok = 1
		BEGIN
			DECLARE @procedura VARCHAR(20)
			DECLARE @undoprocedura VARCHAR(20)

			DECLARE @versiunecurenta INT
			SET @versiunecurenta = (SELECT version FROM DatabaseVersion)

			WHILE(@versiunecurenta < @versiune )
				BEGIN
					SET @versiunecurenta = @versiunecurenta + 1
					SET @procedura = 'procedura' + CAST(@versiunecurenta AS VARCHAR(20))
					EXEC @procedura
				END
			WHILE(@versiunecurenta > @versiune )
				BEGIN
					SET @undoprocedura = 'undoprocedura' + CAST(@versiunecurenta AS VARCHAR(20))
					EXEC @undoprocedura
					SET @versiunecurenta = @versiunecurenta - 1
				END
		END
END

DROP PROCEDURE main

SELECT version FROM DatabaseVersion

EXEC main 1

DECLARE @versiune2 VARCHAR(20)
SET @versiune2 = 'SRFS'
PRINT ISNUMERIC(@versiune2)