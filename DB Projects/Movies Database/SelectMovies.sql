use Filme
go

INSERT INTO Filme(idFilm, numeFilm, dataLansare, durata, popularitate, trailer) VALUES 
(1, 'Interstellar', '2014-11-07', 170, 9, 'https://www.imdb.com/video/vi1586278169?playlistId=tt0816692&ref_=tt_ov_vi'),
(2, 'Colonia', '2016-04-15', 110, 7, 'https://www.imdb.com/video/vi1010678297?playlistId=tt4005402&ref_=tt_ov_vi'),
(3, 'Meet Joe Black', '1998-11-13', 178, 7, 'https://www.youtube.com/watch?v=_zIOjl93WrU'),
(4, 'The Martian', '2015-10-02', 144, 8, 'https://www.imdb.com/video/vi113423129?playlistId=tt3659388&ref_=tt_ov_vi'),
(5, 'The Adjustment Bureau', '2011-03-04', 106, 7, 'https://www.imdb.com/video/vi2215418393?playlistId=tt1385826&ref_=tt_ov_vi'),
(6, 'Oblivion', '2013-04-19', 124, 7, 'https://www.imdb.com/video/vi498116121?playlistId=tt1483013&ref_=tt_ov_vi'),
(7, 'Bohemian Rhapsody', '2018-11-02', 134, 8, 'https://www.imdb.com/video/vi1451538969?playlistId=tt1727824&ref_=tt_ov_vi'),
(8, 'The Imitation Game', '2014-12-25', 104, 8, 'https://www.imdb.com/video/vi3398414105?playlistId=tt2084970&ref_=tt_ov_vi'),
(9, 'Noah', '2014-03-28', 138, 6, 'https://www.imdb.com/video/vi225552921?playlistId=tt1959490&ref_=tt_ov_vi'),
(10, 'The Pursuit of Happyness', '2006-12-15', 117, 8, 'https://www.imdb.com/video/vi1413719065?playlistId=tt0454921&ref_=tt_ov_vi'),
(11, 'Passengers', '2016-12-21', 116, 7, 'https://www.imdb.com/video/vi1586607641?playlistId=tt1355644&ref_=tt_ov_vi'),
(12, 'Limitless', '2011-03-18', 105, 7, 'https://www.imdb.com/video/vi2114755097?playlistId=tt1219289&ref_=tt_ov_vi'),
(13, 'Becoming Jane', '2007-08-10', 160, 7, 'https://www.imdb.com/video/vi2495152409?playlistId=tt0416508&ref_=tt_ov_vi'),
(14, 'The Boy in the Striped Pyjamas', '2008-11-26', 94, 8, 'https://www.imdb.com/video/vi751566873?playlistId=tt0914798&ref_=tt_ov_vi'),
(15, 'Burlesque', '2010-11-24', 119, 6, 'https://www.imdb.com/video/vi1405094169?playlistId=tt1126591&ref_=tt_ov_vi'),
(16, 'Roman Holiday', '1953-09-02', 118, 8, 'https://www.imdb.com/video/vi930856473?playlistId=tt0046250&ref_=tt_ov_vi'),
(17, 'Clueless', '1995-07-19', 97, 7, 'https://www.imdb.com/video/vi993050137?playlistId=tt0112697&ref_=tt_ov_vi'),
(18, 'Pretty Woman', '1990-03-23', 119, 7, 'https://www.imdb.com/video/vi2157232409?playlistId=tt0100405&ref_=tt_ov_vi'),
(19, 'Breakfast at Tiffanys', '1961-10-06', 115, 8, 'https://www.imdb.com/video/vi786734361?playlistId=tt0054698&ref_=tt_ov_vi'),
(20, 'The Lion King', '2019-07-19', 118, 7, 'https://www.imdb.com/video/vi3509369881?playlistId=tt6105098&ref_=tt_ov_vi'),
(21, 'Avatar', '2009-12-18', 162, 8, 'https://www.imdb.com/video/vi531039513?playlistId=tt0499549&ref_=tt_ov_vi'),
(22, 'Inception', '2010-07-16', 148, 9, 'https://www.imdb.com/video/vi2959588889?playlistId=tt1375666&ref_=tt_ov_vi')

SELECT * FROM Filme

INSERT INTO Cinema(idCinema, numeCinema, tara, oras, capacitate) VALUES
(1, 'Royal Cinema', 'Canada', 'Toronto', 200),
(2, 'Teatro Dante', 'Italia', 'Toscana', 150),
(3, 'Ultimate Picture Palace', 'UK', 'Oxford', 100),
(4, 'Paramount Theatre', 'USA', 'OakLand', 250),
(5, 'New Beverly Cinema', 'USA', 'Los Angeles', 400),
(6, 'Cinema Victoria', 'Romania', 'Cluj-Napoca', 200),
(7, 'Le Balzac', 'Franta', 'Paris', 300)

SELECT * FROM Cinema

INSERT INTO Proiectii(idProiectie, idFilm, idCinema, suport3D, suport4D, costBilet, dataProiectie) VALUES
(1, 1, 1, 'DA', 'DA', 200, '2014-12-11 12:30:00'),
(2, 1, 5, 'DA', 'DA', 170, '2015-01-07 14:00:00'),
(3, 2, 7, 'DA', 'NU', 190, '2016-07-31 16:45:00'),
(4, 3, 3, 'NU', 'NU', 100, '2019-06-12 18:00:00'),
(5, 4, 2, 'DA', 'DA', 250, '2020-01-03 20:00:00'),
(6, 4, 6, 'DA', 'NU', 90, '2015-07-09 10:30:00'),
(7, 5, 7, 'DA', 'NU', 100, '2016-07-31 12:00:00'),
(8, 6, 4, 'DA', 'DA', 250, '2018-10-10 13:00:00'),
(9, 7, 6, 'NU', 'NU', 180, '2015-07-09 18:30:00' ),
(10, 7, 5, 'DA', 'NU', 222, '2020-07-31 13:00:00'),
(11, 8, 1, 'NU', 'NU', 120, '2020-01-10 20:00:00'),
(12, 10, 3, 'NU', 'NU', 100, '2019-06-12 10:00:00')

SELECT * FROM Proiectii

INSERT INTO Genuri(numeGen, categorie) VALUES
('SF', 'Science'),
('Romantic', 'Romance'),
('Action', 'Adventure'),
('Drama', 'Serious'),
('Comedy', 'Humor'),
('Animation', 'Cartoon'),
('Fantasy', 'Fiction'),
('Biography', 'History'),
('Thriller', 'Suspense'),
('Musical', 'Music')

SELECT * FROM Genuri

INSERT INTO GenuriFilme(idFilm, numeGen) VALUES
(1, 'SF'),
(1, 'Drama'),
(1, 'Action'),
(2, 'Biography'),
(2, 'Drama'),
(3, 'Drama'),
(3, 'Fantasy'),
(3, 'Romantic'),
(4, 'Drama'),
(4, 'SF'),
(4, 'Action'),
(5, 'Romantic'),
(5, 'SF'),
(5, 'Thriller'),
(6, 'Action'),
(6, 'SF'),
(7, 'Biography'),
(7, 'Drama'),
(7, 'Musical'),
(8, 'Biography'),
(8, 'Drama'),
(8, 'Thriller'),
(9, 'Action'),
(9, 'Drama'),
(10, 'Drama'),
(10, 'Biography'),
(11, 'Drama'),
(11, 'Romantic'),
(11, 'SF'),
(12, 'SF'),
(12, 'Thriller'),
(13, 'Biography'),
(13, 'Drama'),
(13, 'Romantic'),
(14, 'Drama'),
(15, 'Drama'),
(15, 'Musical'),
(16, 'Comedy'),
(16, 'Romantic'),
(17, 'Romantic'),
(17, 'Comedy'),
(18, 'Romantic'),
(18, 'Comedy'),
(19, 'Romantic'),
(19, 'Comedy'),
(19, 'Drama'),
(20, 'Animation'),
(20, 'Action'),
(20, 'Drama'),
(21, 'Action'),
(21, 'Fantasy'),
(22, 'SF'),
(22, 'Action')

SELECT * FROM GenuriFilme

INSERT INTO Melodii(idMelodie, numeMelodie, numeCompozitor, numeInterpret, melodie) VALUES
(1, 'Oh, Pretty Woman', 'Roy Orbison', 'Roy Orbison', 'https://www.youtube.com/watch?v=3KFvoDDs0XM'),
(2, 'Bohemian Rhapsody', 'Queen', 'Queen', 'https://www.youtube.com/watch?v=fJ9rUzIMcZQ'),
(3, 'Moon River', 'Henry Mancini', 'Johnny Mercer', 'https://www.youtube.com/watch?v=p0_lNdDTXYc'),
(4, 'Hakuna Matata', 'Elton John', 'Tim Rice', 'https://www.youtube.com/watch?v=0MxulhivCvI'),
(5, 'Somethings Got a Hold On Me', 'Etta James', 'Christina Aguilera', 'https://www.youtube.com/watch?v=TZFQgqhNoEI'),
(6, 'Bound To You', 'Christina Aguilera', 'Christina Aguilera', 'https://www.youtube.com/watch?v=P52-jyDTNjE'),
(7, 'Love Of My Life', 'Queen', 'Queen', 'https://www.youtube.com/watch?v=sUJkCXE4sAA')

SELECT * FROM Melodii

INSERT INTO ColoanaSonora(idFilm, idMelodie) VALUES
(18, 1),
(7, 2),
(19, 3),
(20, 4),
(15, 5),
(15, 6),
(7, 7)

SELECT * FROM ColoanaSonora

INSERT INTO Regizori(idRegizor, numeRegizor, dataNasterii, bibliografie) VALUES
(1, 'Christopher Nolan', '1970-07-30', 'London, England'),
(2, 'Florian Gallenberger', '1972-02-23', 'Munich, Bavaria, Germany'),
(3, 'Martin Brest', '1951-08-08', 'The Bronx, New York City, New York, USA'),
(4, 'Ridley Scott', '1937-11-30', 'South Shields, Tyne and Wear'),
(5, 'Joseph Kosinski', '1974-05-03', 'Milwaukee, Wisconsin'),
(6, 'Bryan Singer', '1965-09-17', 'New York City, New York, USA'),
(7, 'Morten Tyldum', '1967-05-19', 'Bergen, Norway'),
(8, 'William Wyler', '1902-07-01', 'Mulhausen, Alsace, Germany'),
(9, 'Blake Edwards', '1922-07-26', 'Tulsa, Oklahoma, USA'),
(10, 'Jon Favreau', '1966-10-19', 'Queens, New York City, New York, USA'),
(11, 'George Nolfi', '1968-06-10', 'Boston, Massachusetts'),
(12, 'Darren Aronofsky', '1969-02-12', 'Brooklyn, New York City, New York, USA'),
(13, 'Gabriele Muccino', '1967-05-20', 'Rome, Lazio, Italy'),
(14, 'Julian Jarrold', '1960-05-15', 'Norwich, Norfolk, England, UK')

SELECT * FROM Regizori

INSERT INTO Actori(idActor, numeActor, dataNasterii, bibliografie) VALUES
(1, 'Audrey Hepburn', '1929-05-04', 'Ixelles, Brussels, Belgium'),
(2, 'Will Smith', '1968-09-25', 'Philadelphia, Pennsylvania'),
(3, 'Tom Cruise', '1962-07-03', 'Syracuse, New York, USA'),
(4, 'Emma Watson', '1990-04-15', 'Paris, France'),
(5, 'Matthew McConaughey', '1969-11-04', 'Uvalde, Texas, USA'),
(6, 'Anne Hathaway', '1982-11-12', 'Brooklyn, New York City, New York, USA'),
(7, 'Keira Knightley', '1985-03-26', 'Teddington, England, UK'),
(8, 'Matt Damon', '1970-10-08', 'Boston, Massachusetts, USA'),
(9, 'Rami Malek', '1981-05-12', 'Los Angeles, California, USA'),
(10, 'Jennifer Lawrence', '1990-08-15', 'Louisville, Kentucky, USA')

SELECT * FROM Actori

INSERT INTO Roluri(numeRol, idActor, importanta) VALUES
('Princess Ann', 1, 'Principal'),
('Holly Golightly', 1, 'Principal'),
('Chris Gardner', 2, 'Principal'),
('Jack', 3, 'Principal'),
('Lena', 4, 'Principal'),
('Ila', 4, 'Secundar'),
('Cooper', 5, 'Principal'),
('Brand', 6, 'Secundar'),
('Jane Austen', 6, 'Principal'),
('Joan Clarke', 7, 'Secundar'),
('David Norris', 8, 'Principal'),
('Mark Watney', 8, 'Principal'),
('Freddie Mercury', 9, 'Principal'),
('Aurora Lane', 10, 'Principal')

SELECT * FROM Roluri

INSERT INTO Distributie(idFilm, idActor, idRegizor) VALUES
(1, 5, 7),
(1, 6, 7),
(2, 4, 2),
(4, 8, 4),
(5, 8, 11),
(6, 3, 5),
(7, 9, 6),
(8, 7, 7),
(9, 4, 12),
(10, 2, 13),
(11, 10, 7),
(13, 6, 14),
(16, 1, 8),
(19, 1, 9)

SELECT * FROM Distributie


-- Rezulta numele filmelor si ai actorilor care au numele Tom Cruise, Anne Hathaway sau Audrey Hepburn
SELECT f.numeFilm, a.numeActor
FROM Filme f
INNER JOIN Distributie d ON f.idFilm=d.idFilm
INNER JOIN Actori a ON d.idActor=a.idActor
WHERE a.numeActor IN ('Tom Cruise', 'Anne Hathaway', 'Audrey Hepburn')


-- Rezulta numele actorilor care au jucat in mai mult de un film si numarul de filme jucate
SELECT a.numeActor, COUNT(f.numeFilm) AS 'numarFilme'
FROM Filme f
INNER JOIN Distributie d ON f.idFilm=d.idFilm
INNER JOIN Actori a ON d.idActor=a.idActor
GROUP BY a.numeActor
HAVING COUNT(f.numeFilm)>1


-- Rezulta numele filmelor si al melodiilor lor unde numele filmelor incepe cu litera B
SELECT f.numeFilm, m.numeMelodie
FROM Filme f
INNER JOIN ColoanaSonora c ON f.idFilm=c.idFilm
INNER JOIN Melodii m ON c.idMelodie=m.idMelodie
WHERE  f.numeFilm LIKE 'B%'


-- Rezulta numele disticte ale genurilor filmelor: Interstellar, Oblivion si The Martian
SELECT DISTINCT g.numeGen
FROM Filme f
INNER JOIN GenuriFilme gf ON gf.idFilm=f.idFilm
INNER JOIN Genuri g ON g.numeGen=gf.numeGen
WHERE f.numeFilm IN ('Interstellar', 'Oblivion', 'The Martian')


-- Rezulta numele actorilor care au avut rol Principal si numarul de roluri principale pe care le-au avut
SELECT a.numeActor, COUNT(r.importanta) AS 'numarRoluriPrincipal'
FROM Actori a
INNER JOIN Roluri r ON a.idActor=r.idActor
WHERE r.importanta='Principal'
GROUP BY a.numeActor


-- Rezulta numele cinema-urilor care au suport 3D si numarul de filme la care au suport 3D
SELECT c.numeCinema, COUNT(p.suport3D) AS 'numarSuport3D'
FROM Filme f
INNER JOIN Proiectii p ON f.idFilm=p.idFilm
INNER JOIN Cinema c ON p.idCinema=c.idCinema
WHERE p.suport3D='DA'
GROUP BY c.numeCinema


-- Rezulta numele cinema-urilor si tara in care media costurilor biletelor este mai mica decat 200
SELECT c.numeCinema, c.tara, AVG(p.costBilet) AS 'medieCostBilet'
FROM Filme f
INNER JOIN Proiectii p ON f.idFilm=p.idFilm
INNER JOIN Cinema c ON p.idCinema=c.idCinema
GROUP BY c.numeCinema, c.tara
HAVING AVG(p.costBilet)<200


-- Rezulta numele distincte ale regizorilor tuturor filmelor
SELECT DISTINCT r.numeRegizor
FROM Filme f
INNER JOIN Distributie d ON f.idFilm=d.idFilm
INNER JOIN Regizori r ON r.idRegizor=d.idRegizor


-- Rezulta numele cinema-urilor si a filmelor in care au proiectat filme cu rata de popularitate mai mare ca 7
SELECT c.numeCinema, f.numeFilm
FROM Filme f
INNER JOIN Proiectii p ON f.idFilm=p.idFilm
INNER JOIN Cinema c ON p.idCinema=c.idCinema
WHERE f.popularitate>7


-- Rezulta numele filmelor si a compozitorului care au numele filmului la fel cu numele melodiei
SELECT f.numeFilm, m.numeCompozitor
FROM Filme f
INNER JOIN ColoanaSonora c ON f.idFilm=c.idFilm
INNER JOIN Melodii m ON c.idMelodie=m.idMelodie
WHERE f.numeFilm=m.numeMelodie
