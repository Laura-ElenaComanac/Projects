using System;
using System.Collections.Generic;
using System.Configuration;
using Lab9_MAP.model;
using Lab9_MAP.repository;
using Lab9_MAP.service;
using Lab9_MAP.validator;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab9_MAP
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true) {
                IValidator<Echipa> validatorEchipa = new EchipaValidator();
                string filenameEchipa = ConfigurationManager.AppSettings["echipaFileName"];
                IRepository<string, Echipa> echipaRepo = new EchipaInFileRepository(validatorEchipa, filenameEchipa);
                EchipaService echipaService = new EchipaService(echipaRepo);
                List<Echipa> listEchipe = echipaService.FindAllEchipe();
                //listEchipe.ForEach(x => Console.WriteLine(x));

                IValidator<Elev> validatorElev = new ElevValidator();
                string filenameElev = ConfigurationManager.AppSettings["elevFileName"];
                IRepository<string, Elev> elevRepo = new ElevInFileRepository(validatorElev, filenameElev);
                ElevService elevService = new ElevService(elevRepo);
                List<Elev> listElevi = elevService.FindAllElevi();
                //listElevi.ForEach(x => Console.WriteLine(x));

                IValidator<Jucator> validatorJucator = new JucatorValidator();
                string filenameJucator = ConfigurationManager.AppSettings["jucatorFileName"];
                IRepository<string, Jucator> jucatorRepo = new JucatorInFileRepository(validatorJucator, filenameJucator);
                JucatorService jucatorService = new JucatorService(jucatorRepo, echipaRepo);
                List<Jucator> listJucatori = jucatorService.FindAllJucatori();
                //listJucatori.ForEach(x => Console.WriteLine(x));

                IValidator<Meci> validatorMeci = new MeciValidator();
                string filenameMeci = ConfigurationManager.AppSettings["meciFileName"];
                IRepository<string, Meci> meciRepo = new MeciInFileRepository(validatorMeci, filenameMeci);
                MeciService meciService = new MeciService(meciRepo);
                List<Meci> listMeciuri = meciService.FindAllMeciuri();
                //listMeciuri.ForEach(x => Console.WriteLine(x));

                IValidator<JucatorActiv> validatorJucatorActiv = new JucatorActivValidator();
                string filenameJucatorActiv = ConfigurationManager.AppSettings["jucatorActivFileName"];
                IRepository<string, JucatorActiv> jucatorActivRepo = new JucatorActivInFileRepository(validatorJucatorActiv, filenameJucatorActiv);
                JucatorActivService jucatorActivService = new JucatorActivService(jucatorActivRepo);
                List<JucatorActiv> listJucatoriActivi = jucatorActivService.FindAllJucatoriActivi();
                //listJucatoriActivi.ForEach(x => Console.WriteLine(x));


                Console.WriteLine();
                Console.WriteLine("Meniu Baschet");
                Console.WriteLine();
                Console.WriteLine("1. Sa se afiseze toti jucatorii unei echipe data");
                Console.WriteLine("2. Sa se afiseze toti jucatorii activi ai unei echipe de la un anumit meci");
                Console.WriteLine("3. Sa se afiseze toate meciurile dintr-o anumita perioada calendaristica");
                Console.WriteLine("4. Sa se determine si sa se afiseze scorul de la un anumit meci");
                Console.WriteLine("5. Iesi din aplicatie");
                Console.WriteLine();
                Console.Write("Introduceti comanda: ");

                String c = Console.ReadLine();


                // - Sa se afiseze toti jucatorii unei echipe data
                if (c == "1") 
                {
                    Console.Write("Introduceti numele echipei: ");
                    String numeEchipa = Console.ReadLine();

                    List<String> lista = jucatorService.JucatoriEchipa(numeEchipa);
                    List<String> listaNume = elevService.EleviID(lista);

                    Console.WriteLine();
                    Console.WriteLine("Jucatorii echipei " + numeEchipa + " sunt:");
                    foreach (String jucator in listaNume)
                        Console.WriteLine(jucator);
                    Console.WriteLine();
                }

                // - Sa se afiseze toti jucatorii activi ai unei echipe de la un anumit meci
                if (c == "2") 
                {
                    Console.Write("Introduceti numele echipei: ");
                    String numeEchipa = Console.ReadLine();
                    Console.Write("Introduceti id-ul meciului: ");
                    String idMeci = Console.ReadLine();

                    List<String> listaJucatoriActiviIDMeci = jucatorActivService.JucatoriActiviIDMeci(idMeci);
                    List<String> listaJucatoriActiviIDMeciEchipa = jucatorService.JucatoriActiviIDMeciEchipa(numeEchipa, listaJucatoriActiviIDMeci);
                    List<String> listaJucatoriActiviNume = elevService.EleviID(listaJucatoriActiviIDMeciEchipa);

                    Console.WriteLine();
                    Console.WriteLine("Jucatorii activi ai echipei " + numeEchipa + " din meciul "+ idMeci + " sunt:");
                    foreach (String jucator in listaJucatoriActiviNume)
                        Console.WriteLine(jucator);
                    Console.WriteLine();
                }

                // - Sa se afiseze toate meciurile dintr-o anumita perioada calendaristica
                if (c == "3")
                {
                    Console.Write("Introduceti prima data calendaristica: ");
                    DateTime data1 = DateTime.Parse(Console.ReadLine());
                    Console.Write("Introduceti a doua data calendaristica: ");
                    DateTime data2 = DateTime.Parse(Console.ReadLine());

                    List<Meci> listaMeciuri = meciService.MeciuriPerioada(data1, data2);

                    Console.WriteLine();
                    Console.WriteLine("Meciurile din perioada " + data1 + " - " + data2 + " sunt:");
                    foreach (Meci meci in listaMeciuri)
                        Console.WriteLine(meci.ID + "," + echipaService.IDToNume(meci.idEchipa1) + "," + echipaService.IDToNume(meci.idEchipa2) + "," + meci.data);
                    Console.WriteLine();
                }

                // - Sa se determine si sa se afiseze scorul de la un anumit meci
                if (c == "4") 
                {
                    Console.Write("Introduceti id-ul meciului: ");
                    String idMeci = Console.ReadLine();

                    Tuple<String, String> echipe = meciService.EchipeMeci(idMeci);
                    Tuple<List<String>, List<String>> jucatoriEchipe = jucatorService.JucatoriEchipe(echipe);
                    Tuple<int, int> scor = jucatorActivService.ScorEchipe(jucatoriEchipe);

                    Console.WriteLine();
                    Console.WriteLine("Scorul din meciul " + idMeci + " este: " + scor.Item1 + " - " + scor.Item2);
                    Console.WriteLine();
                }

                if (c == "5") 
                {
                    Console.WriteLine();
                    Console.WriteLine("Ati iesit din aplicatie!");
                    System.Environment.Exit(0);
                }
            }
        }
    }
}
