use FilmeNoi
go

-- CRUD operations

-- functie Filme
GO
CREATE FUNCTION VerificaFilm(@numeFilm VARCHAR(50))
RETURNS INT
AS
BEGIN
	DECLARE @val INT
	IF (@numeFilm = '')
		SET @val = 0
	ELSE
		SET @val = 1
	RETURN @val
END
GO


-- Insereaza, Afiseaza, Modifica si Sterge valori din tabela Filme
CREATE PROCEDURE procedura_Filme
@idFilm INT,
@numeFilm VARCHAR(50),
@dataLansare DATE,
@durata INT,
@popularitate INT,
@trailer VARCHAR(100)
AS
BEGIN 
SET NOCOUNT ON;
       IF (dbo.VerificaFilm(@numeFilm) = 1)
		   BEGIN
				-- Insereaza film
				INSERT INTO Filme(idFilm, numeFilm, dataLansare, durata, popularitate, trailer) VALUES
				(@idFilm, @numeFilm, @dataLansare, @durata, @popularitate, @trailer) 
				-- Afiseaza filmele
				SELECT * FROM Filme
				-- Modifica filmele cu durata 3 care au popularitate > 8
				UPDATE Filme SET durata = 3
				WHERE popularitate > 8
				-- Sterge filmele care incep cu litera 'D'
				DELETE FROM Filme
				WHERE numeFilm LIKE 'D%'

				PRINT 'CRUD efectuat cu succes pentru tabela Filme!'
				RETURN
		   END
      ELSE
		BEGIN
			PRINT 'Numele filmului nu poate fi vid!'
		END
END

DROP PROCEDURE procedura_Filme

EXEC procedura_Filme 1, 'Aino', '12-11-2020', 1, 4, 'trailerA' -- insert
EXEC procedura_Filme 2, 'Dino', '12-11-2020', 1, 4, 'trailerD' -- delete
EXEC procedura_Filme 3, 'Bino', '12-11-2020', 1, 10, 'trailerB' -- update
EXEC procedura_Filme 4, '', '12-11-2020', 1, 10, 'trailerC' -- exceptie

SELECT * FROM Filme
DELETE FROM Filme



-- constrangere Cinema
ALTER TABLE Cinema
ADD CONSTRAINT checkNumeCinema CHECK(numeCinema != '')


-- Insereaza, Afiseaza, Modifica si Sterge valori din tabela Cinema
CREATE PROCEDURE procedura_Cinema
@idCinema INT,
@numeCinema VARCHAR(50),
@tara VARCHAR(50),
@oras VARCHAR(50),
@capacitate INT
AS
BEGIN 
SET NOCOUNT ON;
			BEGIN TRY
				-- Insereaza cinema
				INSERT INTO Cinema(idCinema, numeCinema, tara, oras, capacitate) VALUES
				(@idCinema, @numeCinema, @tara, @oras, @capacitate) 
				-- Afiseaza cinema-uri
				SELECT * FROM Cinema
				-- Modifica cinema-uri cu capacitate 2222 care au tara Romania
				UPDATE Cinema SET capacitate = 2222
				WHERE tara LIKE 'Romania'
				-- Sterge cinema-uri care incep cu litera 'A'
				DELETE FROM Cinema
				WHERE numeCinema LIKE 'A%'

				PRINT 'CRUD efectuat cu succes pentru tabela Cinema!'
			END TRY
			BEGIN CATCH
				PRINT 'Numele cinema-ului nu poate fi vid!'
			END CATCH
END

DROP PROCEDURE procedura_Cinema

EXEC procedura_Cinema 3, 'York', 'America', 'New York', 1000 -- select
EXEC procedura_Cinema 1, 'Albatroz', 'Albania', 'Tirana', 1000 -- delete
EXEC procedura_Cinema 2, 'Victoria', 'Romania', 'Cluj-Napoca', 1000 -- update
EXEC procedura_Cinema 4, '', 'America', 'LA', 1000 -- exceptie

SELECT * FROM Cinema
DELETE FROM Cinema



-- Proiectii
GO
CREATE FUNCTION VerificaProiectie(@idFilm INT, @idCinema INT)
RETURNS INT -- 0 = exista, 1 = film inexistent, 2 = cinema inexistent, 3 = film si cinema inexistente
AS
BEGIN
	DECLARE @rezFilm INT, @rezCinema INT, @var INT
	SET @rezFilm = 0
	SET @rezCinema = 0

	SET @var = 0
	SELECT @var = idFilm FROM Filme WHERE @idFilm = idFilm
	IF (@var = 0)
		SET @rezFilm = 1

	SET @var = 0
	SELECT @var = idCinema FROM Cinema WHERE @idCinema = idCinema
	IF (@var = 0)
		SET @rezCinema = 1

	IF(@rezFilm = 1 AND @rezCinema = 0)
		RETURN 1
	IF(@rezFilm = 0 AND @rezCinema = 1)
		RETURN 2
	IF(@rezFilm = 1 AND @rezCinema = 1)
		RETURN 3
	RETURN 0
END
GO

DROP FUNCTION VerificaProiectie


-- Insereaza, Afiseaza, Modifica si Sterge valori din tabela Proiectii
CREATE PROCEDURE procedura_Proiectii
@idProiectie INT,
@idFilm INT,
@idCinema INT,
@suport3D VARCHAR(2),
@suport4D VARCHAR(2),
@costBilet INT,
@dataProiectie DATETIME
AS
BEGIN 
SET NOCOUNT ON;
       IF (dbo.VerificaProiectie(@idFilm, @idCinema) = 0)
		   BEGIN
				-- Insereaza proiectie
				INSERT INTO Proiectii(idProiectie, idFilm, idCinema, suport3D, suport4D, costBilet, dataProiectie) VALUES
				(@idProiectie, @idFilm, @idCinema, @suport3D, @suport4D, @costBilet, @dataProiectie) 
				-- Afiseaza proiectii
				SELECT * FROM Proiectii
				-- Modifica proiectii cu suport3D 'DA' care au suport3D 'NU'
				UPDATE Proiectii SET suport3D = 'DA'
				WHERE suport3D = 'NU'
				-- Sterge proiectii care au costBilet < 200
				DELETE FROM Proiectii
				WHERE costBilet < 200

				PRINT 'CRUD efectuat cu succes pentru tabela Proiectii!'
				RETURN
		   END
      ELSE
		IF (dbo.VerificaProiectie(@idFilm, @idCinema) = 1)
			BEGIN
				PRINT 'Filmul cu acest ID nu exista!'
			END
		IF (dbo.VerificaProiectie(@idFilm, @idCinema) = 2)
			BEGIN
				PRINT 'Cinema cu acest ID nu exista!'
			END
		IF (dbo.VerificaProiectie(@idFilm, @idCinema) = 3)
		BEGIN
			PRINT 'Cinema si Film cu acest ID nu exista!'
		END
END

DROP PROCEDURE procedura_Proiectii

SELECT * FROM Filme
SELECT * FROM Cinema
SELECT * FROM Proiectii

EXEC procedura_Proiectii 1, 1, 2, 'DA', 'DA', 1000, '12-12-2020' -- insert
EXEC procedura_Proiectii 2, 1, 2, 'NU', 'DA', 1000, '12-12-2020' -- update
EXEC procedura_Proiectii 3, 1, 2, 'DA', 'DA', 10, '12-12-2020' -- delete
EXEC procedura_Proiectii 4, 2, 2, 'DA', 'DA', 1000, '12-12-2020' -- film inexistent
EXEC procedura_Proiectii 5, 1, 1, 'DA', 'DA', 1000, '12-12-2020' -- cinema inexistent
EXEC procedura_Proiectii 6, 2, 1, 'DA', 'DA', 1000, '12-12-2020' -- film si cinema inexistente

DELETE FROM Proiectii
GO
DELETE FROM Filme
GO
DELETE FROM Cinema



-- Popularea tabelelor

CREATE VIEW RandomView
AS
SELECT RAND() AS Value

-- Valoare random dintr-un anumit interval
CREATE FUNCTION random_int(
	@stanga INT,
	@dreapta INT
)
RETURNS INT
AS
BEGIN
	RETURN FLOOR((SELECT Value FROM RandomView) * (@dreapta - @stanga) + @stanga)
END

-- Tabela Filme
CREATE PROCEDURE insereaza_Filme
@val INT
AS
BEGIN
	INSERT INTO Filme(idFilm, numeFilm, dataLansare, durata, popularitate, trailer) VALUES
	(
		@val,
		'Film' + CONVERT(VARCHAR(10), @val),
		CONVERT(VARCHAR(10), dbo.random_int(1,12)) + '-' + CONVERT(VARCHAR(10), dbo.random_int(1,28)) + '-' + CONVERT(VARCHAR(10), dbo.random_int(1980,2020)),
		dbo.random_int(30,120),
		dbo.random_int(1,10),
		'Trailer' + CONVERT(VARCHAR(10), @val)
	)
END


-- Tabela Cinema
CREATE PROCEDURE insereaza_Cinema
@val INT
AS
BEGIN
	INSERT INTO Cinema(idCinema, numeCinema, tara, oras, capacitate) VALUES
	(
		@val,
		'Cinema' + CONVERT(VARCHAR(10), @val),
		'Tara' + CONVERT(VARCHAR(10), @val),
		'Oras' + CONVERT(VARCHAR(10), @val),
		dbo.random_int(50,1000)
	)
END


-- Tabela Proiectii
CREATE PROCEDURE insereaza_Proiectii
@val INT
AS
BEGIN
	INSERT INTO Proiectii(idProiectie, idFilm, idCinema, suport3D, suport4D, costBilet, dataProiectie) VALUES
	(
		@val,
		(SELECT TOP 1 idFilm FROM Filme ORDER BY NEWID()),
		(SELECT TOP 1 idCinema FROM Cinema ORDER BY NEWID()),
		'DA',
		'NU',
		dbo.random_int(50,300),
		CONVERT(VARCHAR(10), dbo.random_int(1,12)) + '-' + CONVERT(VARCHAR(10), dbo.random_int(1,28)) + '-' + CONVERT(VARCHAR(10), dbo.random_int(1980,2020))
	)
END

-- Procedura de populare a tabelelor
CREATE PROCEDURE populeaza_tabela
@nume_tabela VARCHAR(50),
@numar_randuri INT
AS
BEGIN
	DECLARE @rand INT, @comanda VARCHAR(700)
	SET @rand = 1

	WHILE @rand <= @numar_randuri
	BEGIN
		SET @comanda = 'insereaza_' + @nume_tabela + ' ' + CONVERT(VARCHAR(10), @rand)
		EXEC(@comanda)
		SET @rand = @rand + 1
	END
END


EXEC populeaza_tabela 'Filme', 5000
SELECT * FROM Filme
DELETE FROM Filme

EXEC populeaza_tabela 'Cinema', 5000
SELECT * FROM Cinema
DELETE FROM Cinema

EXEC populeaza_tabela 'Proiectii', 5000
SELECT * FROM Proiectii
DELETE FROM Proiectii



--  Views

-- Filme si Proiectii
-- Rezulta numele filmelor care au suport 3D si numarul lor
CREATE VIEW FilmeSuport3DView
AS
SELECT f.numeFilm, COUNT(p.suport3D) AS 'numarSuport3D'
FROM Filme f
INNER JOIN Proiectii p ON f.idFilm=p.idFilm
WHERE p.suport3D='DA'
GROUP BY f.numeFilm

SELECT numeFilm FROM FilmeSuport3DView


-- Filme, Proiectii si Cinema
-- Rezulta numele cinema-urilor si tara in care media costurilor biletelor este mai mica decat 200
CREATE VIEW CinemaTaraMedieBileteView
AS
SELECT c.numeCinema, c.tara, AVG(p.costBilet) AS 'medieCostBilet'
FROM Filme f
INNER JOIN Proiectii p ON f.idFilm=p.idFilm
INNER JOIN Cinema c ON p.idCinema=c.idCinema
GROUP BY c.numeCinema, c.tara
HAVING AVG(p.costBilet)<200

SELECT * FROM CinemaTaraMedieBileteView



-- Indecsi
CREATE NONCLUSTERED INDEX Filme_Index ON Filme (idFilm, popularitate, numeFilm);
DROP INDEX Filme_Index ON Filme

CREATE NONCLUSTERED INDEX Cinema_Index ON Cinema (numeCinema, tara, idCinema);
DROP INDEX Cinema_Index ON Cinema

CREATE NONCLUSTERED INDEX Proiectii_Index ON Proiectii (idFilm, suport3D);
DROP INDEX Proiectii_Index ON Proiectii

CREATE NONCLUSTERED INDEX Proiectii_Index2 ON Proiectii (idFilm, idCinema, costBilet);
DROP INDEX Proiectii_Index2 ON Proiectii


DELETE FROM Proiectii
GO
DELETE FROM Filme
GO
DELETE FROM Cinema
