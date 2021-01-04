CREATE DATABASE TestFilme
go
use TestFilme
go

-------------------------------------------------------------------------------
-- Inserare

-- Inserez teste in tabela Tests
CREATE PROCEDURE create_test
@nume_test VARCHAR(50)
AS
BEGIN
	IF @nume_test IN (SELECT Name FROM Tests)
	BEGIN
		PRINT 'Test deja existent!'
		RETURN
	END
	INSERT INTO Tests (Name) VALUES(@nume_test)
END

EXEC create_test 'test1'

SELECT * FROM Tests


-- Inserez tabelele din BD TestFilme in tabela Tables
CREATE PROCEDURE add_table
@nume_tabela VARCHAR(50)
AS
BEGIN
	IF @nume_tabela NOT IN (SELECT Name FROM Tables)
	BEGIN
		INSERT INTO Tables (Name) VALUES (@nume_tabela)
	END
	ELSE
	BEGIN
		PRINT 'Tabela a fost deja adaugata!'
	END
END

-- O tabela avand un camp ca si cheie primara si nicio cheie straina
EXEC add_table 'Filme'
-- O tabela avand un camp ca si cheie primara si cel putin o cheie straina
EXEC add_table 'Proiectii'
-- O tabela avand doua campuri ca si cheie primara
EXEC add_table 'GenuriFilme'

EXEC add_table 'Cinema'
EXEC add_table 'Genuri'

SELECT * FROM Tables


-- Inserez valori din tabelele Tests si Tables in tabela de legatura TestTables
CREATE PROCEDURE connect_table_to_test
@nume_tabela VARCHAR(50),
@nume_test VARCHAR(50),
@numar_randuri INT,
@pozitie INT
AS
BEGIN
	IF @pozitie <= 0
	BEGIN
		PRINT 'Pozitia trebuie sa fie > 0!'
	END

	IF @numar_randuri <= 0
	BEGIN
		PRINT 'Numarul de randuri trebuie sa fie > 0!'
	END

	DECLARE @id_test INT, @id_tabela INT

	SET @id_test = (SELECT TestID FROM Tests WHERE Name = @nume_test)
	IF @id_test IS NULL
	BEGIN
		PRINT 'Nu exista test cu acel nume!'
		RETURN
	END

	SET @id_tabela = (SELECT TableID FROM Tables WHERE Name = @nume_tabela)
	IF @id_tabela IS NULL
	BEGIN
		PRINT 'Nu exista tabela cu acel nume!'
		RETURN
	END

	BEGIN TRY
		INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES
		(@id_test, @id_tabela, @numar_randuri, @pozitie)
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END

SELECT * FROM TestTables

-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
-- Views

-- Un view ce contine o comanda SELECT pe o tabela
-- Rezulta numele filmelor, trailer-ul si popularitatea, unde popularitatea>8
CREATE VIEW FilmePopulareView
AS
SELECT numeFilm, trailer, popularitate
FROM Filme
WHERE popularitate>8

-- DROP VIEW FilmePopulareView

SELECT * FROM FilmePopulareView


-- Un view ce contine o comanda SELECT aplicata pe cel putin doua tabele
-- Rezulta numele filmelor, trailer-ul si numele genului in care genul este SF
CREATE VIEW FilmeSFView
AS
SELECT f.numeFilm, f.trailer, g.numeGen
FROM Filme f INNER JOIN GenuriFilme g ON g.idFilm = f.idFilm
WHERE g.numeGen Like '%SF%'

-- DROP VIEW FilmeSFView

SELECT * FROM FilmeSFView


-- Un view ce contine o comanda SELECT aplicata pe cel putin doua tabele si avand o clauza GROUP BY
-- Rezulta numele filmelor care au suport 3D si numarul lor
CREATE VIEW FilmeSuport3DView
AS
SELECT f.numeFilm, COUNT(p.suport3D) AS 'numarSuport3D'
FROM Filme f
INNER JOIN Proiectii p ON f.idFilm=p.idFilm
WHERE p.suport3D='DA'
GROUP BY f.numeFilm

-- DROP VIEW FilmeSuport3DView

SELECT * FROM FilmeSuport3DView

-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
-- Inserare2

-- Inserez views in tabela Views
CREATE PROCEDURE add_view
@nume_view VARCHAR(50)
AS
BEGIN
	IF @nume_view NOT IN (SELECT Name FROM Views)
	BEGIN
		INSERT INTO Views (Name) VALUES (@nume_view)
	END
	ELSE
	BEGIN
		PRINT 'View deja adaugat!'
	END
END

EXEC add_view 'FilmePopulareView'
EXEC add_view 'FilmeSFView'
EXEC add_view 'FilmeSuport3DView'

SELECT * FROM Views


-- Inserez valori din tabelele Tests si Views in tabela de legatura TestViews
CREATE PROCEDURE connect_view_to_test
@nume_view VARCHAR(50),
@nume_test VARCHAR(50)
AS
BEGIN
	DECLARE @id_test INT, @id_view INT

	SET @id_test = (SELECT TestID FROM Tests WHERE Name = @nume_test)
	IF @id_test IS NULL
	BEGIN
		PRINT 'Nu exista testul cu acel nume!'
		RETURN
	END

	SET @id_view = (SELECT ViewID FROM Views WHERE Name = @nume_view)
	IF @id_view IS NULL
	BEGIN
		PRINT 'Nu exista view cu acel nume!'
		RETURN
	END

	BEGIN TRY
		INSERT INTO TestViews(TestID, ViewID) VALUES
		(@id_test, @id_view)
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END

SELECT * FROM TestViews

-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
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

-- DROP PROCEDURE insereaza_Filme

EXEC insereaza_Filme 100
SELECT * FROM Filme
DELETE FROM Filme


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

-- DROP PROCEDURE insereaza_Cinema

EXEC insereaza_Cinema 100
SELECT * FROM Cinema
DELETE FROM Cinema


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

-- DROP PROCEDURE insereaza_Cinema

EXEC insereaza_Proiectii 100
SELECT * FROM Proiectii
DELETE FROM Proiectii


-- Tabela Genuri
CREATE PROCEDURE insereaza_Genuri
@val INT
AS
BEGIN
	INSERT INTO Genuri(numeGen, categorie) VALUES
	(
		'SF' + CONVERT(VARCHAR(10), @val),
		'Categorie' + CONVERT(VARCHAR(10), @val)
	)
END

-- DROP PROCEDURE insereaza_Genuri

EXEC insereaza_Genuri 100
SELECT * FROM Genuri
DELETE FROM Genuri


-- Tabela GenuriFilme
CREATE PROCEDURE insereaza_GenuriFilme
@val INT
AS
BEGIN
	DECLARE @generat BIT, @id_film INT, @nume_gen VARCHAR(50)
	SET @generat = 0

	WHILE @generat = 0
	BEGIN
		SET @id_film = (SELECT TOP 1 idFilm FROM Filme ORDER BY NEWID())
		SET @nume_gen = (SELECT TOP 1 numeGen FROM Genuri ORDER BY NEWID())
		IF EXISTS (SELECT * FROM GenuriFilme WHERE idFilm = @id_film AND numeGen = @nume_gen)
		BEGIN
			CONTINUE
		END
		INSERT INTO GenuriFilme(idFilm, numeGen) VALUES
		(
			@id_film,
			@nume_gen
		)
		SET @generat = 1
	END
END

DROP PROCEDURE insereaza_GenuriFilme

EXEC insereaza_GenuriFilme 100
SELECT * FROM GenuriFilme
DELETE FROM GenuriFilme


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

-- DROP PROCEDURE populeaza_tabela

EXEC populeaza_tabela 'Filme', 10000
SELECT * FROM Filme

EXEC populeaza_tabela 'Cinema', 20000
SELECT * FROM Cinema

EXEC populeaza_tabela 'Proiectii', 10000
SELECT * FROM Proiectii

EXEC populeaza_tabela 'Genuri', 20000
SELECT * FROM Genuri

EXEC populeaza_tabela 'GenuriFilme', 10000
SELECT * FROM GenuriFilme

-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
-- TestRuns, TestRunTables si TestRunViews

CREATE PROCEDURE run_test
@nume_test VARCHAR(50)
AS
BEGIN
	DECLARE @id_test INT
	SET @id_test = (SELECT TestID FROM Tests WHERE Name = @nume_test)

	IF @id_test IS NULL
	BEGIN
		PRINT 'Nu exista testul cu acel nume!'
		RETURN
	END

	SET NOCOUNT ON

	-- Tables si TestTables
	DECLARE CursorTables CURSOR SCROLL FOR
		SELECT Tables.TableID, Tables.Name, TestTables.NoOfRows
		FROM TestTables INNER JOIN Tables ON TestTables.TableID = Tables.TableID
		WHERE TestTables.TestID = @id_test
		ORDER BY TestTables.Position

	-- Views si TestViews
	DECLARE CursorViews CURSOR FOR
		SELECT Views.ViewID, Views.Name
		FROM Views INNER JOIN TestViews ON Views.ViewID = TestViews.ViewID
		WHERE TestViews.TestID = @id_test


	DECLARE @tabela VARCHAR(50),
	@numar_randuri INT,
	@pozitie INT,
	@id_tabela INT,
	@start_time_global DATETIME2,
	@end_time_global DATETIME2,
	@start_time_local DATETIME2,
	@end_time_local DATETIME2,
	@id_view INT,
	@view VARCHAR(50),
	@id_test_run INT,
	@comanda VARCHAR(520)

	-- TestRuns
	INSERT INTO TestRuns(Description) VALUES
	('Rezultatele testului pentru ' + @nume_test)

	SET @id_test_run = CONVERT(INT, (SELECT last_value FROM sys.identity_columns WHERE name = 'TestRunID'))

	-- Stergerea datelor  din  tabelele  asociate testului
	SET @start_time_global = SYSDATETIME()

	OPEN CursorTables
	FETCH FIRST FROM CursorTables
	INTO @id_tabela, @tabela, @numar_randuri

	WHILE @@FETCH_STATUS = 0
	BEGIN
		EXEC('DELETE FROM ' + @tabela)

		FETCH NEXT FROM CursorTables
		INTO @id_tabela, @tabela, @numar_randuri
	END

	CLOSE CursorTables

	-- Inserarea inregistrarilor in tabele in ordinea inversa data de Position
	-- TestRunTables
	OPEN CursorTables
	FETCH LAST FROM CursorTables
	INTO @id_tabela, @tabela, @numar_randuri

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @comanda = 'populeaza_tabela ''' + @tabela + ''', ' + CONVERT(VARCHAR(10), @numar_randuri)

		SET @start_time_local = SYSDATETIME()
		EXEC(@comanda)
		SET @end_time_local = SYSDATETIME()

		INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt) VALUES
		(@id_test_run, @id_tabela, @start_time_local, @end_time_local)

		FETCH PRIOR FROM CursorTables
		INTO @id_tabela, @tabela, @numar_randuri
	END

	-- Evaluarea timpului de executie a view-urilor
	-- TestRunViews
	OPEN CursorViews
	FETCH CursorViews
	INTO @id_view, @view
	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @comanda = 'SELECT * FROM ' + @view

		SET @start_time_local = SYSDATETIME()
		EXEC (@comanda)
		SET @end_time_local = SYSDATETIME()

		INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt) VALUES
		(@id_test_run, @id_view, @start_time_local, @end_time_local)

		FETCH CursorViews
		INTO @id_view, @view
	END
	SET @end_time_global = SYSDATETIME()

	UPDATE TestRuns
	SET StartAt = @start_time_global, EndAt = @end_time_global
	WHERE TestRunID = @id_test_run

	CLOSE CursorTables
	CLOSE CursorViews

	DEALLOCATE CursorTables
	DEALLOCATE CursorViews
	SET NOCOUNT OFF
END

-- DROP PROCEDURE run_test

-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
-- Rezultatele testelor

CREATE PROCEDURE results_for_test
@nume_test VARCHAR(50)
AS
BEGIN
	-- TestRuns
	SELECT * FROM TestRuns
	WHERE Description Like '%' + @nume_test + '%'

	-- TestRunTables
	SELECT tt.TestRunID, t.Name, tt.StartAt, tt.EndAt
	FROM TestRunTables tt INNER JOIN Tables t ON tt.TableID = t.TableID
	WHERE tt.TestRunID IN (
		SELECT TestRunID FROM TestRuns
		WHERE Description LIKE '%' + @nume_test + '%'
	)
	ORDER BY StartAt

	-- TestRunViews
	SELECT tv.TestRunID, v.Name, tv.StartAt, tv.EndAt
	FROM TestRunViews tv INNER JOIN Views v ON tv.ViewID = v.ViewID
	WHERE tv.TestRunID IN (
		SELECT TestRunID FROM TestRuns
		WHERE Description LIKE '%' + @nume_test + '%'
	)
	ORDER BY StartAt
END

-- DROP PROCEDURE results_for_test

-- test1

-- TestTables
EXEC connect_table_to_test 'Proiectii', 'test1', 1000, 1
EXEC connect_table_to_test 'GenuriFilme', 'test1', 1000, 2
EXEC connect_table_to_test 'Filme', 'test1', 2222, 3
EXEC connect_table_to_test 'Cinema', 'test1', 3333, 4
EXEC connect_table_to_test 'Genuri', 'test1', 2000, 5


SELECT * FROM TestTables
SELECT * FROM Tables

SELECT T.Name, TT.TestId, TT.NoOfRows, TT.Position
FROM TestTables TT INNER JOIN Tables T ON TT.TableId = T.TableId
ORDER BY TT.Position


SELECT * FROM Tests
SELECT * FROM Views

SELECT * FROM Filme
SELECT * FROM Cinema
SELECT * FROM Proiectii
SELECT * FROM Genuri
SELECT * FROM GenuriFilme

-- TestViews
EXEC connect_view_to_test 'FilmePopulareView', 'test1'
EXEC connect_view_to_test 'FilmeSFView', 'test1'
EXEC connect_view_to_test 'FilmeSuport3DView', 'test1'

SELECT * FROM TestViews
SELECT * FROM Views

EXEC run_test 'test1'
EXEC results_for_test 'test1'

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews

DELETE FROM TestRuns
DELETE FROM TestRunTables
DELETE FROM TestRunViews


-- test2

EXEC create_test 'test2'

EXEC connect_table_to_test 'Proiectii', 'test2', 1000, 1
EXEC connect_table_to_test 'GenuriFilme', 'test2', 1000, 2
EXEC connect_table_to_test 'Filme', 'test2', 2222, 3
EXEC connect_table_to_test 'Cinema', 'test2', 3333, 4
EXEC connect_table_to_test 'Genuri', 'test2', 2000, 5

SELECT * FROM TestTables
SELECT * FROM Tables

SELECT * FROM Filme
SELECT * FROM Cinema
SELECT * FROM Proiectii
SELECT * FROM Genuri
SELECT * FROM GenuriFilme

EXEC connect_view_to_test 'FilmePopulareView', 'test2'
EXEC connect_view_to_test 'FilmeSFView', 'test2'
EXEC connect_view_to_test 'FilmeSuport3DView', 'test2'

SELECT * FROM TestViews
SELECT * FROM Views

EXEC run_test 'test2'
EXEC results_for_test 'test2'

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews

DELETE FROM TestRuns
DELETE FROM TestRunTables
DELETE FROM TestRunViews

-------------------------------------------------------------------------------