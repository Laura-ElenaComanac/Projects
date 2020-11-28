package socialnetwork.service;

import socialnetwork.domain.*;
import socialnetwork.domain.exceptions.AlreadyExistentEntityException;
import socialnetwork.repository.Repository;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.LinkedList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class FriendRequestService {

    private final Repository<Tuple<Long,Long>, FriendRequest> repoFriendRequest;
    private final Repository<Long, Utilizator> repoUtilizator;
    private PrietenieService servicePrietenie;

    public FriendRequestService(Repository<Tuple<Long,Long>, FriendRequest> repoFriendRequest, Repository<Long, Utilizator> repoUtilizator, PrietenieService servicePrietenie){
        this.repoFriendRequest = repoFriendRequest;
        this.repoUtilizator = repoUtilizator;
        this.servicePrietenie = servicePrietenie;
    }

    public List<FriendRequest> getAllFriendRequests(){
        Iterable<FriendRequest> messages = repoFriendRequest.findAll();
        return StreamSupport.stream(messages.spliterator(), false).collect(Collectors.toList());
    }

    public void sendFriendRequest(Utilizator utilizator1, Utilizator utilizator2, LocalDateTime dateTime){
        for(Utilizator util : repoUtilizator.findAll()) {
            if (util.equals(utilizator1))
                utilizator1.setId(util.getId());
            if (util.equals(utilizator2))
                utilizator2.setId(util.getId());
        }

        for(FriendRequest request : getAllFriendRequests())
            if(!request.getStatus().equals("rejected"))
                if(request.getFrom().equals(utilizator1.getId()) && request.getTo().equals(utilizator2.getId()) ||
                     request.getFrom().equals(utilizator2.getId()) && request.getTo().equals(utilizator1.getId()))
                        throw new AlreadyExistentEntityException("Cerere de prietenie deja existenta!");

        String status = "pending";
        FriendRequest friendRequest = new FriendRequest(utilizator1.getId(),utilizator2.getId(),status,dateTime);
        repoFriendRequest.save(friendRequest);
    }

    public List<Utilizator> receivedFriendRequests(Utilizator utilizator){
        for(Utilizator util : repoUtilizator.findAll()) {
            if (util.equals(utilizator))
                utilizator.setId(util.getId());
        }

        List<Utilizator> cereriUtilizator = new LinkedList<>();

        for(FriendRequest friendRequest : getAllFriendRequests()){
            if(friendRequest.getStatus().equals("pending") && utilizator.getId().equals(friendRequest.getTo()))
                cereriUtilizator.add(repoUtilizator.findOne(friendRequest.getFrom()).get());
        }
        return cereriUtilizator;
    }

    public void acceptFriendRequest(Utilizator from, Utilizator to){
        for(Utilizator util : repoUtilizator.findAll()) {
            if (util.equals(from))
                from.setId(util.getId());
            if (util.equals(to))
                to.setId(util.getId());
        }

        for(FriendRequest friendRequest : getAllFriendRequests()) {
            if (friendRequest.getStatus().equals("pending") && from.getId().equals(friendRequest.getFrom()) && to.getId().equals(friendRequest.getTo())) {
                friendRequest.setStatus("approved");
                repoFriendRequest.update(friendRequest);
            }
        }

        ZoneId zid = ZoneId.of("Europe/Bucharest");
        LocalDateTime dt = LocalDateTime.now(zid);
        String date = dt.toString().replace('T', ' ').substring(0,16);
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
        LocalDateTime dateTime = LocalDateTime.parse(date, formatter);

        servicePrietenie.addPrietenie(from, to, dateTime);
    }

    public void rejectFriendRequest(Utilizator from, Utilizator to){
        for(Utilizator util : repoUtilizator.findAll()) {
            if (util.equals(from))
                from.setId(util.getId());
            if (util.equals(to))
                to.setId(util.getId());
        }

        for(FriendRequest friendRequest : getAllFriendRequests()) {
            if (friendRequest.getStatus().equals("pending") && from.getId().equals(friendRequest.getFrom()) && to.getId().equals(friendRequest.getTo())) {
                friendRequest.setStatus("rejected");
                repoFriendRequest.update(friendRequest);
            }
        }
    }
}
