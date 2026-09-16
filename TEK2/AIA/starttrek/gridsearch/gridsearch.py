import itertools
from pathlib import Path
from train import start_train, init_hyperameters

def run_grid_search():
    grid = {
        "LR": [1e-3, 5e-4, 1e-4],
        "GAMMA": [0.99, 0.95],
        "BATCH_SIZE": [64, 128, 256],
        "EPS_DECAY": [1000, 2500, 3500, 5000],
        "EPS_START": [0.8, 0.9, 1.0],
        "EPS_END": [0.001, 0.01, 0.1, 0.2],
        "TAU": [0.005, 0.001, 0.01]
    }

    keys, values = zip(*grid.items())
    combinations = [dict(zip(keys, v)) for v in itertools.product(*values)]
        
    total = len(combinations)
    print(f"Nombre total de combinaisons à tester : {total}")

    for i, combo in enumerate(combinations):
        run_name = f"grid_LR{combo['LR']}_G{combo['GAMMA']}_B{combo['BATCH_SIZE']}_D{combo['EPS_DECAY']}_START{combo['EPS_START']}_END{combo['EPS_END']}TAU{combo['TAU']}"
        if Path(f"runs/{run_name}").exists():
            print(f"[{i+1}/{total}] Skip : {run_name} (Déjà fait)")
            continue
        print(f"\n[{i+1}/{total}] Test en cours : {run_name}")
        custom_config = {
            "hypers": {
                "LR": combo["LR"],
                "GAMMA": combo["GAMMA"],
                "BATCH_SIZE": combo["BATCH_SIZE"],
                "EPS_DECAY": combo["EPS_DECAY"],
                "EPS_START": combo["EPS_START"],
                "EPS_END": combo["EPS_END"],
                "TAU":  combo["TAU"]
            },
            "seed": {"number": [42]},
            "env": {"environment": "LunarLander-v3", "render_mode": "rgb_array"},
            "parameters": {"GRAVITY": -10, "ENABLE_WIND": False}
        }
        try:
            start_train(config_override=custom_config, name_override=run_name)
        except Exception as e:
            print(f"Error in {run_name}: {e}")

if __name__ == "__main__":
    run_grid_search()