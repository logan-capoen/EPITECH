document.getElementById('deleteButton').addEventListener('click', async function() {
    event.preventDefault();
    const id = document.getElementById('idInput').value;

    if (id.length === 0) {
        alert('Enter a valid token');
        return;
    }
    const response = await fetch(`/todos/${id}`, {
        method: 'DELETE',
        headers: {
            'Content-Type': 'application/json',
        },
    });
    if (response.ok) {
        const data = await response.json();
    } else {
        console.log("Error");
    }
});
